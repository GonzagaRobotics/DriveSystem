#include <Arduino.h>
#include <string.h>
#include "Depends/vars.h"
#include "Depends/functions.h"
#include "motorFunctions.h"
#include "debugs.h"
#include "SerialBridge.h"
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
        Serial.print("MOTOR_DRIVER_READY");
    }
    else
    {
        Serial.print("MOTOR_DRIVER_STARTING");
        delay(1500);
    }
    if (driverError == 1)
    {
        Serial.print("The Motor Driver has errored.\n If you are seeing this message, Michael left DEBUGGING on. Please contact him.\n Damon: If you see this, BanHammer me.\n");
    }
}

void loop()
{
    opperatingLoop();
}

void opperatingLoop()
{
    // DEBUG: TAKE SERIAL INPUT

    // Decode the incoming Command from ROS
    decodeCommand();
    // Use the serial command to drive the motors
    motorDriver();
}