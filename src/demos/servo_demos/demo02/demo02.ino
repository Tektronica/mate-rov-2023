#include <Servo.h>

#define SERVO_PIN 9         // Pin to control the servo motor
#define SERVO_MIN_ANGLE 0   // Minimum angle for the servo motor
#define SERVO_MAX_ANGLE 180 // Maximum angle for the servo motor
#define SERVO_DELAY 1000    // Delay in milliseconds between movements

Servo myservo; // create a servo object

void setup()
{
    // Set up serial communication
    Serial.begin(9600); // initialize the serial port
    while (!Serial)
    {
        // await serial interface
    }; 

    // Set up the servo motor
    myservo.attach(SERVO_PIN); // attaches the servo motor to the pin defined as SERVO_PIN
}

void loop()
{
    // Rotate the servo motor to the maximum angle
    Serial.println("Rotating servo motor to maximum angle...");
    myservo.write(SERVO_MAX_ANGLE);
    delay(SERVO_DELAY);

    // Rotate the servo motor to the minimum angle
    Serial.println("Rotating servo motor to minimum angle...");
    myservo.write(SERVO_MIN_ANGLE);
    delay(SERVO_DELAY);
}
