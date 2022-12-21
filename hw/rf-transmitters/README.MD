# 2.4GHz vs. Bluetooth

Both Bluetooth and many comercial transceivers, such as the nRF24L01+, transmit over 2.4GHz. However, 

## nRF24L01+
RF modules can only transmit to the same module or family supported by that device. Companies such as Nordic Semiconductor develop their own proprietary transmit protocol.

## HC-05
Bluetooth modules are generally device agnostic. This means any standard blueooth module can pair with any other bluetooth module. However, the device first *must* be paired prior to transmitting data. Consequently, in applications where data transmision is aperiodic, a generic RF modules is preferred over Bluetooth.

# Final Thoughts
For Arduino to Arduino communication, the nRF24L01+ is a well supported device in the community. Consequently, not much will be involved in setting up RX/TX communication.

For Arduino to PC (or phone) communication, Bluetooth is required. Otherwise a custom interface using the NRF24L01+ or a private Wi-Fi access point must be established. 


# sources
[Bluetooth module vs wireless module Arduino](https://arduino.stackexchange.com/a/78265)
