#ifndef BUOY_MCU_H_
#define BUOY_MCU_H_

// initialize the arduino MCU and peripherals
void init_MCU();
// wrapper for Serial.println();
template <typename T>
void MCU_serialPrint(T message);
// get elapsed time since initialization
unsigned long MCU_getTimeElapsed();

#endif /* BUOY_MCU_H_ */
