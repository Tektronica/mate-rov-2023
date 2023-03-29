#include <SPI.h>
#include <RF24.h>

#define CE_PIN 10
#define CSN_PIN 11

const uint8_t MESSAGE_SIZE = 32;
const uint8_t MAX_RETRIES = 5;
const uint8_t MESSAGE_TIMEOUT = 5000; // 5 second timeout for receiving a message

// Define the radio number and pipe addresses for each device
const uint8_t RADIO_NUMBER = 0;              // Radio number used by the device
const uint64_t MASTER_PIPE = 0xE8E8F0F0E1LL; // Master pipe address
const uint64_t SLAVE_PIPE = 0xE8E8F0F0E2LL;  // Slave pipe address

// Define the RF24 radio object
RF24 radio(CE_PIN, CSN_PIN); // CE, CSN

// Function declarations
void initializeSerial();
void initializeRadio();
void setRadioAddresses();
bool sendMessage(char *message);
bool sendResponse(char *response);
bool receiveMessage(char *messageBuffer, uint8_t bufferSize);
bool waitForMessage(char *messageBuffer, uint8_t bufferSize);

void setup()
{
    initializeSerial();
    initializeRadio();
    setRadioAddresses();
    radio.startListening();
}

void loop()
{
    if (RADIO_NUMBER == 0)
    {
        // Send a message to the slave device
        const char *message = "PING";

        Serial.println("Sending message: PING");
        if (sendMessage(message))
        {

            // Wait for a response from the slave device
            char response[MESSAGE_SIZE];
            uint8_t responseSize = MESSAGE_SIZE;
            if (receiveMessage(response, responseSize))
            {
                Serial.print("Received response: ");
                Serial.println(response);
            }
            else
            {
                Serial.println("Failed to receive response");
            }
        }
        else
        {
            Serial.println("Failed to send message");
        }
        delay(1000); // wait before sending next message
    }
    else
    {
        // Wait for a message from the master device
        char message[MESSAGE_SIZE];
        uint8_t messageSize = MESSAGE_SIZE;
        if (waitForMessage(message, messageSize))
        {
            Serial.print("Received message: ");
            Serial.println(message);

            // Send a response to the master device
            const char *response = "PONG";
            Serial.print("Send response: ");
            Serial.println(response);
            if (!sendResponse(response))
            {
                Serial.println("Failed to send response");
            }
        }
        else
        {
            Serial.println("Failed to receive message");
        }
    }
}
void initializeSerial()
{
    // Initialize serial communication
    Serial.begin(9600);
}

void initializeRadio()
{
    // Initialize the RF24 radio
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoRetransmit(MAX_RETRIES, 10);
}

void setRadioAddresses()
{
    // Set the radio addresses
    if (RADIO_NUMBER == 0)
    {
        radio.openWritingPipe(MASTER_PIPE);
        radio.openReadingPipe(1, SLAVE_PIPE);
    }
    else
    {
        radio.openWritingPipe(SLAVE_PIPE);
        radio.openReadingPipe(1, MASTER_PIPE);
    }
}

bool sendMessage(const char *message)
{
    // Send a message with retransmissions
    bool success = false;
    uint8_t retries = 0;
    radio.stopListening();
    while (!success && retries <= MAX_RETRIES)
    {
        success = radio.write(message, strlen(message) + 1);
        retries++;
    }
    radio.startListening();
    if (!success)
    {
        Serial.println("Failed to send message");
    }
    return success;
}

bool receiveMessage(char *messageBuffer, uint8_t bufferSize)
{
    uint32_t startTime = millis();
    while (!radio.available())
    {
        if (millis() - startTime > MESSAGE_TIMEOUT)
        {
            return false;
        }
    }

    uint8_t len = radio.getDynamicPayloadSize();
    if (len > bufferSize - 1)
    {
        len = bufferSize - 1;
    }

    radio.read(messageBuffer, len);
    messageBuffer[len] = '\0';

    return true;
}

bool sendResponse(char *response)
{
    // Send a response
    bool success;
    radio.stopListening();
    success = radio.write(response, strlen(response) + 1);
    radio.startListening();
    if (!success)
    {
        Serial.println("Failed to send response");
    }
    return success;
}

bool waitForMessage(char *messageBuffer, uint8_t bufferSize)
{
    uint8_t pipe;
    uint32_t startTime = millis();
    while (!radio.available(&pipe))
    {
        if (millis() - startTime > MESSAGE_TIMEOUT)
        {
            return false;
        }
    }

    uint8_t len = radio.getDynamicPayloadSize();
    len = len > bufferSize - 1 ? bufferSize - 1 : len;

    radio.read(messageBuffer, len);
    messageBuffer[len] = '\0';

    return true;
}