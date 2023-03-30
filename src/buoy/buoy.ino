/*
    File ........ buoy.ino
    Author ...... Tektronica
    Type ........ Application layer

    wokwi example:  https://wokwi.com/projects/351808292414030415
*/

#include "buoy.h"
#include "buoy-mcu.h"
#include "buoy-radio.h"
#include "buoy-motor.h"
#include <ctime>

enum Status status;

unsigned long buoy_utc = 0;

void setup()
{
    init_MCU();       // initialize board and Arduino
    init_radio();     // initialize radio
    init_motor();     // initialize stepper motor
    status = SURFACE; // set initial buoy status
}

void loop()
{
    switch (status)
    {
    case SURFACE:
        transmit();
        break;

    case UNDERWATER:
        dataCollect();
        break;

    case ASCEND:
        ascend();
        break;

    case DESCEND:
        descend();
        break;

    default:
        // no default for now
        break;
    }
}

bool isValidUTC(unsigned long utc_time)
{
    // get the current UTC time in seconds
    unsigned long current_time = time(nullptr);

    // calculate the maximum difference between the current time and the received UTC time
    unsigned long max_difference = 60; // allow for a 1 minute difference

    // check if the received UTC time is within the valid range
    if (utc_time >= current_time - max_difference && utc_time <= current_time + max_difference)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void transmit()
{
    radio_wake();                                                    // turn on radio
    MCU_serialPrint("transmit");                                     // log serial
    unsigned long utc_with_millis = buoy_utc + MCU_getTimeElapsed(); // add the elapsed time to the buoy UTC value
    radio_send(utc_with_millis);                                     // transmit data

    unsigned long response = radio_read(); // wait for response
    if (isValidUTC(response))              // check if response is a valid UTC value
    {
        // update buoy's UTC value and log the new value
        buoy_utc = response;
        MCU_serialPrint("Updated buoy UTC value.");
    }

    radio_sleep(); // once transmitted and received, sleep the radio

    // once data has transmitted, go back underwater
    status = DESCEND;
}

void dataCollect()
{
    MCU_serialPrint("collect");

    // once data collection complete, go back to the surface
    status = ASCEND;
}

void descend()
{
    // motor will turn clockwise until condition met
    // once complete or has been interrupted, status will change
    if (!motor_clockwise())
    {
        MCU_serialPrint("underwater");

        // once descended, collect data underwater
        status = UNDERWATER;

        // delay after descent complete
        delay(500);
    }
}

void ascend()
{
    // motor will turn counter-clockwise until condition met
    // once complete or has been interrupted, status will change
    if (!motor_counterclockwise())
    {
        MCU_serialPrint("reached surface");

        // once ascended, transmit data at surface
        status = SURFACE;

        // delay after descent complete
        delay(500);
    }
}
