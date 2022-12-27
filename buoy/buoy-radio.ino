/*
    File ........ buoy-tx.ino
    Author ...... Tektronica
    Type ........ Peripheral layer

    Example:        pingpair_sleepy.ino
    https://nrf24.github.io/RF24/examples_2old_backups_2pingpair_sleepy_2pingpair_sleepy_8ino-example.html
    https://nrf24.github.io/RF24/examples_2GettingStarted_2GettingStarted_8ino-example.html
    https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
    https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
*/

#include "buoy-mcu.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

// Single radio pipe address for the 2 modules to communicate
// TX "address" writes over "pipe" and the RX must know that address
const uint64_t slaveAddress = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN); // create new instance of driver

void init_radio()
{
    MCU_serialPrint("setup transmit");

    radio.begin();                       // begin operation of the chip.
    radio.setDataRate(RF24_250KBPS);     // Set the transmission data rate.
    radio.setRetries(15, 15);            // retries and delay upon failed submit.
    radio.openWritingPipe(slaveAddress); // open writing pipe to destination
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

    // write to the open writing pipe
    bool rslt = radio.write(&message, sizeof(message));
    // Always use sizeof() as it gives the size as the number of bytes.
    // For example if dataToSend was an int sizeof() would correctly return 2

    MCU_serialPrint((String) "Data Sent " + message);

    // true if the payload was delivered successfully false if not 
    if (rslt) {
        MCU_serialPrint("Acknowledge received");
    } else {
        MCU_serialPrint("Tx failed");
    }
}

unsigned long radio_read()
{
    // switch to receive mode
    radio.startListening();

    unsigned long data;

    // if there is data ready
    if (radio.available()) {

        while (radio.available()) {
            // Read payload data from the RX FIFO buffer(s)
            radio.read(&data, sizeof(data));
            return data;
        }
    }
    return 0;
}
