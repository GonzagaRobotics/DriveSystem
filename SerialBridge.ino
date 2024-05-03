#include <Arduino.h>
#include "Depends/vars.h"

void decodeCommand()
{
    Serial.readBytes(inputStream, MAX_BYTES);
    for (int i = 0; i < MAX_BYTES; i++)
    {
        if (inputStream[i] == 'E' && inputStream[i + 1] == 'N')
        {
            // enable
            enable = true;
        }
        if (inputStream[i] == 'F' && inputStream[i + 1] == 'W')
        {
            // forward
            directionForward = (((i + 2)) + (i + 3));
        }
        if (inputStream[i] == 'B' && inputStream[i + 1] == 'W')
        {
            // backward
            directionBackward = (((i + 2)) + (i + 3));
        }
        if (inputStream[i] == '\0' && inputStream[i + 1] == 'L')
        {
            // left
            directionLeft = (((i + 2)) + (i + 3));
        }
        if (inputStream[i] == '\0' && inputStream[i + 1] == 'R')
        {
            // right
            directionRight = (((i + 2)) + (i + 3));
        }
    }