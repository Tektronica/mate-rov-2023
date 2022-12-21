// constants --------------------------------------------------------------------------------------
unsigned long startMillis;

// variables --------------------------------------------------------------------------------------
unsigned long currentMillis;
unsigned long elapsedMillis;
unsigned long txIntervalMillis = 1000; // send once per second

// ------------------------------------------------------------------------------------------------
void init_MCU()
{
    Serial.begin(9600);      // initialize the serial port
    while (!Serial) {};      // await serial interface
    startMillis = millis();  // get first time
}

// ------------------------------------------------------------------------------------------------
template <typename T>
void MCU_serialPrint(T message)
{
    Serial.println(message);
}

unsigned long MCU_getTimeElapsed()
{
    currentMillis = millis();
    elapsedMillis = currentMillis - startMillis;

    return elapsedMillis;
}
