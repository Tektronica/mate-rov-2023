// Include the Arduino Stepper Library
#include <Stepper.h>

// Define Constants -------------------------------------------------------------------------------
const float STEPS_PER_REV = 32; // Number of steps per internal motor revolution
const float GEAR_RED = 16;      // Amount of Gear Reduction

// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED; 

// Define Variables -------------------------------------------------------------------------------
int StepsRequired; // Number of Steps Required

// defines pins numbers ---------------------------------------------------------------------------
const int stepPin = 3;
const int dirPin = 4;

/*
 set direction and step pin
 Create Instance of Stepper Class
 Specify Pins used for motor coils
 The pins used are 8,9,10,11
 Connected to ULN2003 Motor Driver In1, In2, In3, In4
 Pins entered in sequence 1-3-2-4 for proper step sequencing
*/
Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);

void setup()
{
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // digitalWrite(dirPin,LOW); //Enables the motor to move in a particular direction
}
void loop()
{
  delay(60000);
  for (int i = 0; i < 12; i++) {
    // Rotate CCW 1/2 turn quickly
    StepsRequired = -STEPS_PER_OUT_REV / 2;
    steppermotor.setSpeed(700);
    steppermotor.step(StepsRequired);
    delay(0.1);
  }

  {
    // Enables the motor to move in a particular direction
    digitalWrite(dirPin, LOW); 

    // Makes 200 pulses for making one full cycle rotation
    for (int i = 0; i < 5000; i++){
      digitalWrite(stepPin, HIGH); // reverse rotation direction
      delayMicroseconds(1000);     // delay by 1 sec

      digitalWrite(stepPin, LOW); // reverse rotation direction
      delayMicroseconds(1000);    // delay by 1 sec
    }

    delay(10000);               // delay by 10 sec
    digitalWrite(dirPin, HIGH); // reverse rotation direction

    for (int i = 0; i < 5000; i++) {
      digitalWrite(stepPin, HIGH); // reverse rotation direction
      delayMicroseconds(1000);     // delay by 1 sec

      digitalWrite(stepPin, LOW);  // reverse rotation direction
      delayMicroseconds(1000);     // delay by 1 sec
    }

    delay(2000);
    return (0);
  }
}