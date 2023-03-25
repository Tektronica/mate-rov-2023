/*
    File ........ buoy-mcu.ino
    Author ...... Tektronica
    Type ........ MCU layer (Arduino)
*/

#include <avr/wdt.h> //include avr Watchdog timer liberary

// heartbeat --------------------------------------------------------------------------------------
#define heartbeat_pin 13        // heartbeat LED pin
bool heartbeat_status = false; // heartbeat state

// constants --------------------------------------------------------------------------------------
unsigned long startMillis; // "technically" a constant

// variables --------------------------------------------------------------------------------------
unsigned long currentMillis;
unsigned long elapsedMillis;
unsigned long txIntervalMillis = 1000; // send once per second

// declarations -----------------------------------------------------------------------------------

// watchdog interrupt
void init_watchdog();

// ------------------------------------------------------------------------------------------------
void init_MCU()
{
    pinMode(heartbeat_pin, OUTPUT); // Set LED pin as an OUTPUT
    init_watchdog();                // watchdog interrupt

    Serial.begin(9600); // initialize the serial port
    while (!Serial) {}; // await serial interface
}

// ------------------------------------------------------------------------------------------------

void init_watchdog()
{
    cli();                                            // Disable all interrupt occurring
    WDTCSR = (1 << WDCE) | (1 << WDE);                // enable Watchdog interrupt
    WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1); // 1s WDT interrupt interval
    sei();
}

// heartbeat
ISR(WDT_vect)
{
    heartbeat_status = !heartbeat_status;         // flip heartbeat state
    digitalWrite(heartbeat_pin, heartbeat_status); // write to pin
}

// ------------------------------------------------------------------------------------------------
template <typename T>
void MCU_serialPrint(T message)
{
    // template <typename T>
    Serial.println(message);
}

unsigned long MCU_getTimeElapsed()
{
    currentMillis = millis();
    elapsedMillis = currentMillis - startMillis;

    return elapsedMillis;
}
