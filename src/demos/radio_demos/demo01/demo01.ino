#include <SPI.h>
#include <RF24.h>

// Define the radio number and pipe addresses for each device
const uint8_t RADIO_NUMBER = 0;              // Radio number used by the device
const uint64_t MASTER_PIPE = 0xE8E8F0F0E1LL; // Master pipe address
const uint64_t SLAVE_PIPE = 0xE8E8F0F0E2LL;  // Slave pipe address

// Define the RF24 radio object
RF24 radio(7, 8); // CE, CSN

// Define the maximum number of retries for failed transmissions
const uint8_t MAX_RETRIES = 5;

void setup()
{
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the RF24 radio
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoRetransmit(MAX_RETRIES, 10);

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

    // Start listening for incoming messages
    radio.startListening();
}

void loop()
{
    if (RADIO_NUMBER == 0)
    {
        // Send a message to the slave device
        const char *message = "PING";
        Serial.println("Sending message: PING");
        radio.stopListening();
        bool success = radio.write(message, strlen(message) + 1);
        radio.startListening();

        // Wait for a response from the slave device
        if (success)
        {
            uint8_t pipe;
            unsigned long start_time = micros();
            while (!radio.available(&pipe))
            {
                if (micros() - start_time > 100000)
                {
                    Serial.println("Response timed out");
                    break;
                }
            }
            if (radio.available(&pipe))
            {
                char response[32];
                radio.read(response, 32);
                Serial.print("Received response: ");
                Serial.println(response);
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
        uint8_t pipe;
        unsigned long start_time = micros();
        while (!radio.available(&pipe))
        {
            if (micros() - start_time > 100000)
            {
                Serial.println("Message timed out");
                break;
            }
        }
        if (radio.available(&pipe))
        {
            char message[32];
            radio.read(message, 32);
            Serial.print("Received message: ");
            Serial.println(message);

            // Send a response to the master device
            const char *response = "PONG";
            Serial.print("Send response: ");
            Serial.println(response);
            bool success = radio.write(response, strlen(response) + 1);
            if (!success)
            {
                Serial.println("Failed to send response");
            }
        }
    }
}
