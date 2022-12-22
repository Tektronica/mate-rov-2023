#include "buoy-mcu.h"
#include <AccelStepper.h>

// Define a stepper and the pins it will use
const int stepPin = 3;      // pin sets step size
const int directionPin = 2; // pin sets motor direction
const int enablePin = 5;

AccelStepper stepper(AccelStepper::DRIVER, stepPin, directionPin);

void init_motor()
{
    MCU_serialPrint("setup motor");
    stepper.setEnablePin(enablePin);
    stepper.setPinsInverted(false, false, true);
    stepper.enableOutputs();

    stepper.setAcceleration(50); // desired acceleration in steps per second per second
    stepper.setMaxSpeed(1000);   // desired maximum speed in steps per second
    stepper.setSpeed(0);         // desired constant speed in steps per second
}

void motor_resetPosition()
{
    // resets the current position of the motor to 0
    stepper.setCurrentPosition(0);
}

void motor_clockwise()
{
    /*
        Clockwise moves the motor to the target position (with acceleration/deceleration)
        With a 16MHz Arduino (such as Uno or Mega) the AccelStepper max rpm is roughly 4000 steps per second.
        Note: code blocking until position reached.
    */
    MCU_serialPrint("cw");
    stepper.runToNewPosition(100); // Negative is anticlockwise from the 0 position
}

void motor_counterclockwise()
{
    /*
        Counter-clockwise moves the motor to the target position (with acceleration/deceleration)
        With a 16MHz Arduino (such as Uno or Mega) the AccelStepper max rpm is roughly 4000 steps per second.
        Note: code blocking until position reached.
        
    */
    MCU_serialPrint("ccw");
    stepper.runToNewPosition(-100); // Negative is anticlockwise from the 0 position
}
