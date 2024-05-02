#include <Arduino.h>
#include "Depends/vars.h"

void decodeCommand()
{
    Serial.readBytes(inputStream, MAX_BYTES);

    // TODO: Add command decoding
}