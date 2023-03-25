#ifndef BUOY_COMMUNICATE_H_
#define BUOY_COMMUNICATE_H_

// initialize the TX operation
void init_radio();
// Power down the radio
void radio_sleep();
// Power up the radio
void radio_wake();
// transmit data
template <typename T>
void radio_send(T message);
// Read payload data from the RX FIFO buffer(s)
unsigned long radio_read();

#endif /* BUOY_COMMUNICATE_H_ */