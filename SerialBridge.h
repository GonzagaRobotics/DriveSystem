#include <Arduino.h>
#include "Depends/vars.h"

void commandParser()
{
    int moveLeftMotor = tempMotorSpeed;
    int moveRightMotor = tempMotorSpeed;
}
void decodeCommand()
{
    // Serial.readBytes(inputStream, MAX_BYTES);
    //  Convert Bytes to ASCII
    for (int i = 0; i < MAX_BYTES; i++)
    {
        outputStream[i] = char(inputStream[i]);
        Serial.print(outputStream[i]);
    }
    // Parse the Command
    commandParser();
    // Clear all arrays
    for (int i = 0; i < MAX_BYTES; i++)
    {
        inputStream[i] = 0;
        outputStream[i] = 0;
    }
    int tempMotorSpeed = Serial.read();
}
