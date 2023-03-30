#include <SPI.h>
#include <RF24.h>

#define CE_PIN 10
#define CSN_PIN 11
#define MESSAGE_SIZE 32
#define MAX_RETRIES 5

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
void sendMessage(const char *message);
void sendResponse(const char *response);
void waitForMessage(char *messageBuffer);

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
        sendMessage(message);

        // Wait for a response from the slave device
        char response[MESSAGE_SIZE];
        waitForMessage(response);
        Serial.print("Received response: ");
        Serial.println(response);
        delay(1000); // wait before sending next message
    }
    else
    {
        // Wait for a message from the master device
        char message[MESSAGE_SIZE];
        waitForMessage(message);
        Serial.print("Received message: ");
        Serial.println(message);

        // Send a response to the master device
        const char *response = "PONG";
        Serial.print("Send response: ");
        Serial.println(response);
        sendResponse(response);
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
    // Send a message
    bool success;
    radio.stopListening();
    success = radio.write(message, strlen(message) + 1);
    radio.startListening();
    if (!success)
    {
        Serial.println("Failed to send message");
    }
    return success;
}

bool sendResponse(const char *response)
{
    // Send a response
    bool success = radio.write(response, strlen(response) + 1);
    if (!success)
    {
        Serial.println("Failed to send response");
    }
    return success;
}

void waitForMessage(char *messageBuffer)
{
    // Wait for a message
    uint8_t pipe;
    while (!radio.available(&pipe))
    {
        radio.read(messageBuffer, MESSAGE_SIZE);
    }
}
