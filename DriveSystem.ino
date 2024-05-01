#include <Arduino.h>
#include "vars.cpp"
#include "motorControl.cpp"
void setup()
{
    Serial.begin(9600);
    Serial.print("Starting Motor Drive System... Please Wait.");
    void initializeMotorDriver();
    if (driverReady == 1)
    {
        Serial.write("MOTOR_DRIVER_READY");
    }
    else
    {
        Serial.write("MOTOR_DRIVER_STARTING");
        delay(1500);
    }
}

void loop()
{
    void motorDriver();
}