
#include "buoy-mcu.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 10
#define CSN_PIN 11

const uint8_t MAX_RETRIES = 5;
const uint32_t MESSAGE_TIMEOUT = 5000; // 5 second timeout for receiving a message

// Define the radio number and pipe addresses for each device
const uint8_t RADIO_NUMBER = 0;              // Radio number used by the device
const uint64_t MASTER_PIPE = 0xE8E8F0F0E1LL; // Master pipe address
const uint64_t SLAVE_PIPE = 0xE8E8F0F0E2LL;  // Slave pipe address

RF24 radio(CE_PIN, CSN_PIN); // create new instance of driver

void init_radio()
{
    MCU_serialPrint("setup transmit");

    // Initialize the RF24 radio
    radio.begin(); // begin operation of the chip.
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoRetransmit(MAX_RETRIES, 10);
    setRadioAddresses();
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

// --------------------------------------------------------------------------------------------------------------------
void radio_sleep()
{
    // Power up the radio after sleeping
    radio.powerDown();
}

void radio_wake()
{
    // NOTE: The radio MUST be powered back up again manually
    radio.powerUp();
}

// --------------------------------------------------------------------------------------------------------------------
template <typename T>
void radio_send(T message)
{
    // switch to transmit mode
    radio.stopListening();

    // Wait for the radio to switch to transmit mode
    delay(5);

    // write to the open writing pipe
    bool rslt = radio.write(&message, sizeof(T));

    MCU_serialPrint("Data Sent");

    if (rslt)
    {
        // true if the payload was delivered successfully
        MCU_serialPrint("Acknowledge received");
    }
    else
    {
        // false if no ACK was returned
        MCU_serialPrint("No ACK returned");
    }
}

unsigned long radio_read()
{
    // switch to receive mode
    radio.startListening();

    unsigned long data = 0;

    unsigned long start_time = millis();
    while (millis() - start_time < MESSAGE_TIMEOUT)
    {
        // if there is data ready
        if (radio.available())
        {
            // Read payload data from the RX FIFO buffer(s)
            radio.read(&data, sizeof(data));
            break; // exit loop if data is received
        }
    }

    // switch back to transmit mode
    radio.stopListening();

    return data;
}
