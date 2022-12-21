#include "buoy.h"
#include "buoy-mcu.h"
#include "buoy-motor.h"

enum Status status;

void setup()
{
    init_MCU();
    init_motor();
    status = SURFACE; // set initial buoy status
}

void loop()
{
    switch (status)
    {
    case SURFACE:
        transmit();
        status = DESCEND;
        break;

    case UNDERWATER:
        dataCollect();
        status = ASCEND;
        break;

    case ASCEND:
        ascend();
        status = SURFACE;
        break;

    case DESCEND:
        descend();
        status = UNDERWATER;
        break;
    }
}

void transmit()
{
    MCU_serialPrint("transmit");
    MCU_serialPrint(MCU_getTimeElapsed());
}

void dataCollect()
{
    MCU_serialPrint("collect");
}

void descend()
{
    // step one revolution  in one direction:
    MCU_serialPrint("descending");
    motor_counterclockwise();
    delay(500);
}

void ascend()
{
    // step one revolution in the other direction:
    MCU_serialPrint("ascending");
    motor_clockwise();
    delay(500);
}
