#ifndef BUOY_COMMUNICATE_H_
#define BUOY_COMMUNICATE_H_

// initialize the TX operation
void init_TX();
// transmit data
void rf_transmit();
// update the message after each sucessful read
void updateMessage(); // TODO: Remove this

#endif /* BUOY_COMMUNICATE_H_ */