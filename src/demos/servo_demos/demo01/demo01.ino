#include <Servo.h>

#define SERVO_PIN 9

Servo myservo;    // create a servo object

void setup()
{
    myservo.attach(SERVO_PIN); // attaches the servo on pin 9 to the servo object
}

void loop()
{
    myservo.write(90); // sets the servo position to 90 degrees
    delay(1000);       // waits for 1 second

    myservo.write(0);  // sets the servo position to 0 degrees
    delay(1000);       // waits for 1 second
}
