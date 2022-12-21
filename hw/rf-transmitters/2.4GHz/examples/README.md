# Introduction

The nRF24L01+ 2.4GHz transceiver modules are cheap and very effective but I have come across a few Threads in which people were having trouble with them so I thought it might be useful to gather together in one place a basic step-by-step sequence for getting them to work.

# TMRh20 version of the RF24 library

This tutorial uses the TMRh20 version of the RF24 library 49 which fixes some problems in the earlier ManiacBug version. Unfortunately, however, TMRh20 did not think to give his version a different name so it can be difficult to be certain which one is on your PC. If, before reading this, you have downloaded and installed the RF24 library the simplest thing may be to delete all traces of it and then download and install the TMrh20 version. Note that the demo programs will NOT work with the ManiacBug version of the library.

# nRF24L01+ module pin connections

The nRF24 modules that I am using look like this.
With the pins uppermost and the antenna on the right hand side the pin connections are

# Arduino connections

Because the nRF24s use SPI to communicate with the Arduino they must use Arduino pins 13, 12 and 11 (SCK, MISO and MOSI). It is also necessary to connect the CSN and CE pins and any of the Arduino I/O pins can be used for them. However for demo purposes it seems easiest to use pins 10 and 9 so that all 5 connections are adjacent on pins 13 to 9. I use some female-male jumper wires to connect to the nRF24 for test and development. The jumper wires come as a piece of ribbon cable and if you separate a piece with 5 wires and allocate the wires to suit the Arduino pins it is very easy to connect and disconnect the nRF24 from the Arduino without getting the connections mixed up.

If you are using pins other than 10 and 9 for CSN and CE you must still set pin 10 for OUTPUT to ensure that the Uno acts as the SPI master.

# Powering the nRF24L01+ module

The nRF24 modules require a 3.3v power supply. Be careful NOT to connect the VCC pin to a 5v power supply. I have found that they work satisfactorily when connected to the 3.3v pin on my Unos.

It is recommended to plce a 10µF capacitor across VCC and GND as near to the module as possible and I have found this essential when I made some units with an Atmega328 chip on a breadboard. The capacitor stabilizes the power supply for the module. However I have not found it necessary to use a capacitor with my Uno (or Mega). But if you believe you have followed all the other instructions correctly and are having problems it would certainly be a good idea to install a capacitor.

# Resetting the nRF24

It seems that on some occasions the nRF24 does not reset after a new program is uploaded to the Arduino. This can prevent the program from working properly. If you think that is the case then disconnect the Arduino from the USB cable and reconnect it.

# Some of the jargon explained

Because the nRF24s are transceivers they can obviously transmit and receive. To try to avoid confusion I will assume that you are using one them (which I will refer to as TX or "master") to transmit and another one (RX or "slave") to receive.

Like a lot of other equipment (WiFi and Bluetooth, for example) the nRF24L01+ modules broadcast on the 2.4GHz band. The precise frequency is determined by the channel that is selected. Both TX and RX must use the same channel. The default channel for the RF24 library is 76.

When the TX sends a message every RX listening on the same channel will receive the message. The TX includes an "address" in the message and the RX will ignore messages that do not have its address. The address is similar in concept to a phone number except that you cannot easily change the number of your phone. The address is a 5 byte number.

The nRF24L01+ modules can listen on any or all of 6 "pipes". Unfortunately in some RF24 demo programs the variable that is used to hold the address is given the name "pipe" even though pipes and addresses are quite different. For the purpose of this tutorial I will only be using one pipe (pipe 1) for listening. Note that pipe 0 is the only writing pipe. It is possible to listen on pipe 0 but it is simpler to leave that excusively for writing.

The 6 pipes allow an nRF24 to listen for messages from 6 other devices with 6 different addresses. But those devices may not transmit at the exact same time.

# Radio interference

Note that if 2 or more TXs transmit at the same time on the same channel they will interfere with each other and the message will not be receivable. That is why an NRF24 cannot receive messages on its 6 pipes at the same instant.

Messages will also be garbled if (say) a nearby Wifi system transmits at the same time on the exact same frequency.

However each individual transmission is very short (a few millisecs) so that it is unlikely that the transmission from your TX will overlap with something else.

# Data Packets

The nRF24L01+ modules can transmit a maximum of 32 bytes in a single message. If you need to send more you will need to break it into a number of separate messages. For this tutorial I will not be sending more than 32 bytes.

There are two modes of operation {A} a fixed payload size which defaults to 32 bytes and can be changed with setPayloadSize() and {B} a dynamic payload mode which is chosen with enableDynamicPayloads(). The dynamic payload mode is automatically applied when you choose the ackPayload feature (see Example 2). You can check the payload size with getDynamicPayloadSize().

When using dynamic payloads you must ensure that you read all the bytes that are received or the communication will break down.

# Data validation

The nRF24s automatically include sophisticated systems to identify whether the data received matches the data that was sent. If the data is not received correctly the RX will not show data available() and will not send an acknowledgment. That means the TX will consider the transmission to have failed. You will see in the example programs that the TX is instructed automatically to retry the transmission up to 5 time before giving up. (The max is 15).

In your RX code you can therefore assume that if data is available() it will be correct.

Also note that, unlike Arduino Serial communication, when the RF24 library shows data as available() it means that the entire mesage has been correctly received.

# Reference

[Simple nRF24L01+ 2.4GHz transceiver demo](https://forum.arduino.cc/t/simple-nrf24l01-2-4ghz-transceiver-demo/405123/4)