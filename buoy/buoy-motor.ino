/*
    File ........ buoy-motor.ino
    Author ...... Tektronica
    Type ........ Peripheral layer

    wokwi example: https://wokwi.com/projects/351808292414030415
*/

#include "buoy-mcu.h"
#include <AccelStepper.h>

// Define a stepper and the pins it will use
const int stepPin = 3;      // pin sets step size
const int directionPin = 2; // pin sets motor direction
const int enablePin = 5;
bool motorStop = false; // motor interrupt

AccelStepper stepper(AccelStepper::DRIVER, stepPin, directionPin);

void init_motor()
{
    MCU_serialPrint("setup motor");
    stepper.setEnablePin(enablePin);
    stepper.setPinsInverted(false, false, true);
    stepper.enableOutputs();

    // with a 16MHz Arduino (such as Uno or Mega) the AccelStepper max rpm is roughly 4000 steps per second.
    stepper.setAcceleration(50); // desired acceleration in steps per second per second

    stepper.setMaxSpeed(1000);   // desired maximum speed in steps per second
    stepper.setSpeed(0);         // desired constant speed in steps per second
}

void motor_run()
{
	// poll the motor and step it if a step is due
	// implements acceleration to achieve the target position
	stepper.run();

	// reset position to zero when complete
	if (stepper.distanceToGo() == 0) {
		stepper.setCurrentPosition(0);
	}
}

bool motor_clockwise()
{
	if (!stepper.isRunning()) {
		// set the target position
		stepper.moveTo(200);
	}

    // run motor with acceleration to a target
	motor_run();
    
    // return bool of current status of motor
	return stepper.isRunning();
}

bool motor_counterclockwise()
{
	if (!stepper.isRunning()) {
		// set the target position (negative is anticlockwise)
		stepper.moveTo(-200);
	}

    // run motor with acceleration to a target
	motor_run();

    // return bool of current status of motor
	return stepper.isRunning();
}
