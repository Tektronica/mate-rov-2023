/*
    File ........ buoy-mcu.ino
    Author ...... Tektronica
    Type ........ MCU layer (Arduino)
*/

#include <avr/wdt.h> //include avr Watchdog timer liberary

// heartbeat --------------------------------------------------------------------------------------
#define heartbeat_pin 13       // heartbeat LED pin
bool heartbeat_status = false; // heartbeat state

// constants --------------------------------------------------------------------------------------
static unsigned long startMillis; // "technically" a constant

// variables --------------------------------------------------------------------------------------
unsigned long currentMillis;
unsigned long elapsedMillis;
unsigned long txIntervalMillis = 1000; // send once per second

// declarations -----------------------------------------------------------------------------------

// watchdog interrupt
void init_watchdog();

// ------------------------------------------------------------------------------------------------

// initialize the MCU
void init_MCU()
{
    pinMode(heartbeat_pin, OUTPUT); // Set LED pin as an OUTPUT

    Serial.begin(9600); // initialize the serial port
    while (!Serial)
    {
        // await serial interface
    };
    init_watchdog(); // watchdog interrupt
}

// ------------------------------------------------------------------------------------------------

// watchdog interrupt
ISR(WDT_vect)
{
    heartbeat_status = !heartbeat_status;          // flip heartbeat state
    digitalWrite(heartbeat_pin, heartbeat_status); // write to pin
}

// initialize watchdog
void init_watchdog()
{
    cli();                                            // Disable all interrupt occurring
    WDTCSR = (1 << WDCE) | (1 << WDE);                // enable Watchdog interrupt
    WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1); // 1s WDT interrupt interval
    sei();
}

// ------------------------------------------------------------------------------------------------
// print message to serial port
template <typename T>
void MCU_serialPrint(T message)
{
    Serial.println(message);
}

// get elapsed time since program started
unsigned long MCU_getTimeElapsed()
{
    static unsigned long currentMillis;
    static unsigned long elapsedMillis;
    currentMillis = millis();
    elapsedMillis = currentMillis - startMillis;

    return elapsedMillis;
}