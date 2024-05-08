#include <Arduino.h>
#include "Depends/vars.h"

void commandParser()
{
    if (outputStream[0] == 'F')
    {
        moveDirection = 1;
        moveLeftMotor = 255;
        moveRightMotor = 255;
    }
    else if (outputStream[0] == 'B')
    {
        moveDirection = -1;
        moveLeftMotor = 255;
        moveRightMotor = 255;
    }
    else if (outputStream[0] == 'L')
    {
        moveDirection = 2;
        moveLeftMotor = 255;
        moveRightMotor = 255;
    }
    else if (outputStream[0] == 'R')
    {
        moveDirection = -2;
        moveLeftMotor = 255;
        moveRightMotor = 255;
    }
    else if (outputStream[0] == 'S')
    {
        moveDirection = 0;
        moveLeftMotor = 0;
        moveRightMotor = 0;
    }
    else
    {
        moveDirection = 0;
        moveLeftMotor = 0;
        moveRightMotor = 0;
    }
}
void decodeCommand()
{
    Serial.readBytes(inputStream, MAX_BYTES);
    // Convert Bytes to ASCII
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
}
