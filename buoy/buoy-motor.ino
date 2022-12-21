#include "buoy-mcu.h"
#include <Stepper.h>

const int stepsPerRevolution = 200;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void init_motor()
{
    MCU_serialPrint("setup motor");
    myStepper.setSpeed(60); // set the speed at 60 rpm:
}

void motor_clockwise()
{
    // clockwise step motor
    MCU_serialPrint("cw");
    myStepper.step(stepsPerRevolution);
}

void motor_counterclockwise()
{
    // counterclockwise step motor
    MCU_serialPrint("ccw");
    myStepper.step(-stepsPerRevolution);
}
