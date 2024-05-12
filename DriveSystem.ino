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
    Serial.println("Starting Motor Drive System... Please Wait.");
    do
    {
        initializeMotorDriver();

    } while (driverReady != 1);
    if (driverReady == 1)
    {
        Serial.println("MOTOR_DRIVER_READY");
    }
    else
    {
        Serial.println("MOTOR_DRIVER_STARTING");
        delay(1500);
        initializeMotorDriver();
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
    // Report back to ROS
    serialBuilder();
    sendSerialToROS();
}