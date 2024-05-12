#include <Arduino.h>
#include <string.h>
#include "Depends/vars.h"

void commandParser()
{
    // We recieve 12 bytes from the serial port
    // The data is split into 4 byte chunks. The first 2 bytes of each chunk
    // are the key, the last 2 bytes are the value

    // The key is a 2 char that represents the command

    // Split the 12 bytes into strings, with the split occuring every 4 bytes
    //  Split the array into 4 byte strings
    char key[2];
    char value[2];
    for (int i = 0; i < 12; i += 4)
    {
        // Split the array into 4 byte strings
        key[0] = outputStream[i];
        key[1] = outputStream[i + 1];
        value[0] = outputStream[i + 2];
        value[1] = outputStream[i + 3];
        // Convert the value to an integer
        int valueInt = atoi(value);
        // Check the key and set the value
        if (strcmp(key, "EN") == 0)
        {
            if (valueInt == 1)
            {
                enable = 1;
            }
            else
            {
                enable = 0;
            }
        }
        else
        {
            // If The key is NOT EN, we know that we are sending direction commands
            // Therefore, we need to od math (ew)

            // Convert the 32some thousand to a better number
            // To make my lfe easier, I convert everything to positive values (im a lazy bastard)
            if (valueInt < 0)
            {
                valueInt = (valueInt * -1.0);
                invertDirection = true;
            }

            // Time for MORE MATH! Yay!
            // Here we divide by 256 to do magic happiness
            valueInt = (valueInt / 256.0);

            if (strcmp(key, "FB") == 0)
            {
                Serial.print("FB");
                motorSpeedFB = valueInt;
            }
            else if (strcmp(key, "LR") == 0)
            {
                Serial.print("LR");
                motorSpeedLR = valueInt;
            }
        }
    }
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
}

void serialBuilder()
{
    int enableStatus = enable;
    String EN = ("EN" + String(enableStatus));
    String FL = ("DP" + String(frontLeftDP) + "AP" + String(frontLeftAP) + "CR" + String(frontLeftRPM) + "CA" + String(frontLeftTC));
    String FR = ("DP" + String(frontRightDP) + "AP" + String(frontRightAP) + "CR" + String(frontRightRPM) + "CA" + String(frontRightTC));
    String CL = ("DP" + String(centerLeftDP) + "AP" + String(centerLeftAP) + "CR" + String(centerLeftRPM) + "CA" + String(centerLeftTC));
    String CR = ("DP" + String(centerRightDP) + "AP" + String(centerRightAP) + "CR" + String(centerRightRPM) + "CA" + String(centerRightTC));
    String RL = ("DP" + String(rearLeftDP) + "AP" + String(rearLeftAP) + "CR" + String(rearLeftRPM) + "CA" + String(rearLeftTC));
    String RR = ("DP" + String(rearRightDP) + "AP" + String(rearRightAP) + "CR" + String(rearRightRPM) + "CA" + String(rearRightTC));
}
void sendSerialToROS()
{
    String ROSString = (EN + "FL" + FL + "FR" + FR + "CL" + CL + "CR" + CR + "RL" + RL + "RR" + RR);
}