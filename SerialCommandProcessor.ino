#include <Arduino.h>
#include "Depends/vars.h"

void decodeCommand()
{
    String incomingSerial = Serial.readString();
    if (incomingSerial == "ESTOP")
    {
        // Set the driver ready flag to 0
        driverReady = 0;
        for (int i = 0; i < 3; i++)
        {
            analogWrite(leftMotorGroup[i], 0);
            analogWrite(rightMotorGroup[i], 0);
        }
    }
    // TODO: Add command decoding
}