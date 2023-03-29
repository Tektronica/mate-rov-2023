#include <Servo.h>

// Define servo motor connections and maximum angle
#define SERVO_PIN 3   // Pin to control the servo motor
#define MAX_ANGLE 180 // Maximum angle for the servo motor

// Create an instance of the Servo library for the servo motor
Servo servoMotor;

// Define the functions for clockwise and counter-clockwise rotation
bool clockwise()
{
    if (!servoMotor.attached())
    {
        Serial.println("Attaching servo motor...");
        servoMotor.attach(SERVO_PIN);
    }
    if (servoMotor.read() < MAX_ANGLE)
    {
        Serial.println("Rotating servo motor clockwise...");
        servoMotor.write(servoMotor.read() + 1);
    }
    return servoMotor.read() < MAX_ANGLE;
}

bool counterClockwise()
{
    if (!servoMotor.attached())
    {
        Serial.println("Attaching servo motor...");
        servoMotor.attach(SERVO_PIN);
    }
    if (servoMotor.read() > 0)
    {
        Serial.println("Rotating servo motor counter-clockwise...");
        servoMotor.write(servoMotor.read() - 1);
    }
    return servoMotor.read() > 0;
}

void setup()
{
    // Set up serial communication
    Serial.begin(9600); // initialize the serial port
    while (!Serial)
    {
        // await serial interface
    };

    // Set up the pins for the servo motor
    servoMotor.attach(SERVO_PIN);

    // Move the servo motor to its initial position (0 degrees)
    servoMotor.write(0);
}

void loop()
{
    bool running = true;
    while (running)
    {
        running = clockwise();
    }

    // Pause for one second before rotating the servo motor counter-clockwise
    Serial.println("Pausing for one second...");
    delay(1000);

    running = true;
    while (running)
    {
        running = counterClockwise();
    }

    // Pause for one second before starting over
    Serial.println("Pausing for one second...");
    delay(1000);
}
