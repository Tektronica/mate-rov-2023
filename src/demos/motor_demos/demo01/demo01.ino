#include <AccelStepper.h>

// Define stepper motor connections and steps per revolution
#define DIRECTION_PIN 2  // Pin to set the direction of the stepper motor rotation
#define STEP_PIN 3       // Pin to send step pulses to the stepper motor driver
#define ENABLE_PIN 4     // Pin to enable the stepper motor driver

#define MS1_PIN 5          // Pin to set the microstepping mode of the stepper motor driver
#define MS2_PIN 6          // Pin to set the microstepping mode of the stepper motor driver
#define MS3_PIN 7          // Pin to set the microstepping mode of the stepper motor driver
#define STEPS_PER_REV 200  // Number of steps per revolution for the stepper motor

// Define the maximum speed and acceleration for the stepper motor
#define MAX_SPEED 2000    // Maximum speed in steps per second
#define ACCELERATION 500  // Acceleration in steps per second squared
#define MICROSTEPS 32     // number of microsteps to complete one full step

// Create an instance of the AccelStepper library for the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIRECTION_PIN);

void setup() {
  // Set up serial communication
  Serial.begin(9600);  // initialize the serial port
  while (!Serial) {};  // await serial interface

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

void loop() {
  // Rotate the stepper motor clockwise for one revolution
  Serial.println("Rotating motor clockwise...");
  stepper.move(MICROSTEPS * STEPS_PER_REV);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  // Pause for one second before rotating the stepper motor counter-clockwise
  Serial.println("Pausing for one second...");
  delay(1000);

  // Rotate the stepper motor counter-clockwise for one revolution
  Serial.println("Rotating motor counter-clockwise...");
  stepper.move(-MICROSTEPS * STEPS_PER_REV);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  // Pause for one second before starting over
  Serial.println("Pausing for one second...");
  delay(1000);
}
