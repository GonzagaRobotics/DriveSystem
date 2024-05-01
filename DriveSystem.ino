#include <Arduino.h>
#include "Depends/vars.h"
#include "Depends/functions.h"
#include "motorFunctions.ino"
void setup()
{
    Serial.begin(9600);
    Serial.print("Starting Motor Drive System... Please Wait.");
    do
    {
        void initializeMotorDriver();

    } while (driverReady != 1);
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