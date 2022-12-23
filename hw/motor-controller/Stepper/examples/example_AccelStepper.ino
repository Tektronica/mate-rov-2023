/*
	Description ... Perpetually alternates the direction of motor rotation
	Author ........ Tektronica

	Wokwi simulation: https://wokwi.com/projects/351808292414030415
*/

#include <AccelStepper.h>

// Define a stepper and the pins it will use
const int stepPin = 3;		// pin sets step size
const int directionPin = 2; // pin sets motor direction
const int enablePin = 5;
bool motorStop = false; // motor interrupt

enum Status
{
	CW,
	CCW
};

Status status = CW;
AccelStepper stepper(AccelStepper::DRIVER, stepPin, directionPin);

void setup()
{
	Serial.begin(9600); // initialize the serial port
	while (!Serial) {}; // await serial interface

	Serial.println("setup motor");
	stepper.setEnablePin(enablePin);
	stepper.setPinsInverted(false, false, true);
	stepper.enableOutputs();

	stepper.setAcceleration(50); // desired acceleration in steps per second per second
	stepper.setMaxSpeed(1000);	 // desired maximum speed in steps per second
	stepper.setSpeed(0);		 // desired constant speed in steps per second
}

void loop()
{
	switch (status) {
	case CW:
		// motor will turn clockwise until condition met
		// once complete or has been interrupted, status will change
		if (!motor_clockwise()) {
			Serial.println("cw done");
			status = CCW;
		}
		break;

	case CCW:
		// motor will turn counter-clockwise until condition met
		// once complete or has been interrupted, status will change
		if (!motor_counterclockwise()) {
			Serial.println("ccw done");
			status = CW;
		}
		break;

	default:
		{
			// nothing for now
		}
	}
}

void motor_run()
{
	// poll the motor and step it if a step is due
	// implements acceleration to achieve the target position
	stepper.run();

	if (stepper.distanceToGo() == 0) {
		// reset position to zero when complete
		stepper.setCurrentPosition(0);
	}
}

bool motor_clockwise()
{
	if (!stepper.isRunning()) {
		// set the target position
		stepper.moveTo(200);
	}

	motor_run();

	// once motor has stopped
	return stepper.isRunning();
}

bool motor_counterclockwise()
{
	if (!stepper.isRunning()) {
		// set the target position (negative is anticlockwise)
		stepper.moveTo(-200);
	}

	motor_run();
	return stepper.isRunning();
}
