#include <Arduino.h>
#include "Depends/vars.h"

void decodeCommand()
{
    Serial.readBytes(inputStream, MAX_BYTES);
    for (int i = 0; i < MAX_BYTES; i++)
    {
        if (inputStream[i] == 'E')
        {
        }
        if (inputStream[i] == 'F')
        {
        }
        if (inputStream[i] == 'B')
        {
        }
        if (inputStream[i] == 'L')
        {
        }
        if (inputStream[i] == 'R')
        {
        }
    }
    // TODO: Add command decoding
}