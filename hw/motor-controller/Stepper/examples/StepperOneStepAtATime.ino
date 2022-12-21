/*
Stepper one step at a time
Turn the shaft step by step to check the proper wiring of the motor.
https://www.arduino.cc/reference/en/libraries/stepper/
*/

#include <Stepper.h>

// change this to fit the number of steps per revolution
const int stepsPerRevolution = 200; 

// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// number of steps the motor has taken
int stepCount = 0; 

void setup()
{
  // initialize the serial port:
  Serial.begin(9600);
}

void loop()
{
  // step one step:
  myStepper.step(1);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount++;
  delay(500);
}
