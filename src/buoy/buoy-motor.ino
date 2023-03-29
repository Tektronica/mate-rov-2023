/*
	File ........ buoy-motor.ino
	Author ...... Tektronica
	Type ........ Peripheral layer

	wokwi example: https://wokwi.com/projects/351808292414030415
*/

#include "buoy-mcu.h"
#include <AccelStepper.h>

// Define stepper motor connections and steps per revolution
#define DIRECTION_PIN 2 // Pin to set the direction of the stepper motor rotation
#define STEP_PIN 3		// Pin to send step pulses to the stepper motor driver
#define ENABLE_PIN 4	// Pin to enable the stepper motor driver

#define MS1_PIN 5				// Pin to set the microstepping mode of the stepper motor driver
#define MS2_PIN 6				// Pin to set the microstepping mode of the stepper motor driver
#define MS3_PIN 7				// Pin to set the microstepping mode of the stepper motor driver
#define STEPS_PER_REV 200		// Number of steps per revolution for the stepper motor
#define NUMBER_OF_REVOLUTIONS 5 // number of revolutions made

// Define the maximum speed and acceleration for the stepper motor
#define MAX_SPEED 3000	 // Maximum speed in steps per second
#define ACCELERATION 500 // Acceleration in steps per second squared
#define MICROSTEPS 32	 // number of microsteps to complete one full step

// Create an instance of the AccelStepper library for the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIRECTION_PIN);

void init_motor()
{
	// Set up serial communication
	Serial.begin(9600); // initialize the serial port
	while (!Serial)
	{
		// await serial interface
	};

	// Set the maximum speed and acceleration for the stepper motor
	stepper.setMaxSpeed(MAX_SPEED);
	stepper.setAcceleration(ACCELERATION);

	// Set up the pins for the DRV8825 controller
	pinMode(ENABLE_PIN, OUTPUT);
	pinMode(MS1_PIN, OUTPUT);
	pinMode(MS2_PIN, OUTPUT);
	pinMode(MS3_PIN, OUTPUT);

	// Set the microstepping mode to 1/32
	digitalWrite(MS1_PIN, HIGH);
	digitalWrite(MS2_PIN, HIGH);
	digitalWrite(MS3_PIN, HIGH);

	// Enable the stepper motor
	digitalWrite(ENABLE_PIN, LOW);
}

void motor_run()
{
	// poll the motor and step it if a step is due
	// implements acceleration to achieve the target position
	stepper.run();
}

// Define the functions for clockwise and counter-clockwise rotation
bool motor_clockwise()
{
	if (!stepper.isRunning())
	{
		Serial.println("Rotating motor clockwise...");
		stepper.moveTo(MICROSTEPS * STEPS_PER_REV * NUMBER_OF_REVOLUTIONS);
	}
	// run motor with acceleration to a target

	motor_run();
	// return bool of current status of motor
	return stepper.isRunning();
}

bool motor_counterclockwise()
{
	if (!stepper.isRunning())
	{
		Serial.println("Rotating motor counter-clockwise...");
		stepper.moveTo(0);
	}
	// run motor with acceleration to a target
	motor_run();
	// return bool of current status of motor
	return stepper.isRunning();
}
