#include <Arduino.h>
#include <string.h>
#include "Depends/vars.h"
#include "Depends/functions.h"
#include "motorFunctions.ino"
#include "SerialCommandProcessor.ino"
void setup()
{
    Serial.begin(9600);
    Serial.print("Starting Motor Drive System... Please Wait.");
    do
    {
        initializeMotorDriver();

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
    opperatingLoop();
}

void opperatingLoop()
{
    // Decode the incoming Command from ROS
    decodeCommand();
    // Use the serial command to drive the motors
    motorDriver();
}