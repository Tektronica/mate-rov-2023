/*
    File ........ buoy.ino
    Author ...... Tektronica
    Type ........ Application layer

    wokwi example: https://wokwi.com/projects/351808292414030415
*/

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
    switch (status) {
    case SURFACE:
        transmit();
        break;

    case UNDERWATER:
        dataCollect();
        break;

    case ASCEND:
        ascend();
        break;

    case DESCEND:
        descend();
        break;

    default:
    {
        // no default for now
    }
    }
}

void transmit()
{
    MCU_serialPrint("transmit");
    MCU_serialPrint(MCU_getTimeElapsed());

    // once data has transmitted, go back underwater
    status = DESCEND;
}

void dataCollect()
{
    MCU_serialPrint("collect");

    // once data collection complete, go back to the surface
    status = ASCEND;
}

void descend()
{
    // motor will turn clockwise until condition met
    // once complete or has been interrupted, status will change
    if (!motor_clockwise()) {
        MCU_serialPrint("underwater");

        // once descended, collect data underwater
        status = UNDERWATER;

        // delay after descent complete
        delay(500);
    }
}

void ascend()
{
    // motor will turn counter-clockwise until condition met
    // once complete or has been interrupted, status will change
    if (!motor_counterclockwise()) {
        MCU_serialPrint("reached surface");

        // once ascended, transmit data at surface
        status = SURFACE;

        // delay after descent complete
        delay(500);
    }
}
