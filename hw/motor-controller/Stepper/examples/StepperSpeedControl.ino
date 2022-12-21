/*
Stepper speed control
Control the stepping speed with a potentiometer.
https://www.arduino.cc/reference/en/libraries/stepper/
*/ 

#include <Stepper.h>

// change this to fit the number of steps per revolution
const int stepsPerRevolution = 200; 

// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0; // number of steps the motor has taken
void setup() {}    // nothing to do inside the setup

void loop()
{
  // read the sensor value:
  int sensorReading = analogRead(A0);

  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);

  // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution / 100);
  }
}
