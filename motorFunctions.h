#include "Depends/vars.h"
void initializeMotorDriver()
{ // Define the motor pins
    int motorFrontLeft = 3;
    int motorCenterLeft = 5;
    int motorBackLeft = 6;
    int motorFrontRight = 9;
    int motorCenterRight = 10;
    int motorBackRight = 11;
    // Create an array for the motor groups
    int leftMotorGroup[3] = {motorFrontLeft, motorCenterLeft, motorBackLeft};
    // and the same for the right
    int rightMotorGroup[3] = {motorFrontRight, motorCenterRight, motorBackRight};
    // Set the motor pins to output
    for (int i = 0; i < 3; i++)
    {
        pinMode(leftMotorGroup[i], OUTPUT);
        pinMode(rightMotorGroup[i], OUTPUT);
    }
    // Set the motor pins to 0
    for (int i = 0; i < 3; i++)
    {
        analogWrite(leftMotorGroup[i], 0);
        analogWrite(rightMotorGroup[i], 0);
    }
    // Set the driver ready flag to 1
    driverReady = 1;
}

void motorDriver()
{
    // We know the speed and direction. But, we need to seperate things out. First, we check to see
    // If F/B or L/R equals 0

    // Left/Right
    if (motorSpeedFB == 0)
    {
        // If the FB value is 0, that means we are addressing L/R Movement
        if (invertDirection == false)
        {
            for (int i = 0; i < 3; i++)
            {
                analogWrite(leftMotorGroup[i], motorSpeedLR);
                analogWrite(rightMotorGroup[i], 0);
            }
        }
        if (invertDirection == true)
        {
            for (int i = 0; i < 3; i++)
            {
                analogWrite(leftMotorGroup[i], 0);
                analogWrite(rightMotorGroup[i], motorSpeedLR);
            }
        }
    }
    else
    {
        // Forward-Backwards
        if (motorSpeedLR == 0)
        {
            if (invertDirection == false)
            {
                for (int i = 0; i < 3; i++)
                {
                    analogWrite(leftMotorGroup[i], motorSpeedFB);
                    analogWrite(rightMotorGroup[i], motorSpeedFB);
                }
            }
            if (invertDirection == true)
            {
                // Remember how we un negatived that number?
                // Well its negative again. Yeah.
                motorSpeedFB = (motorSpeedFB * -1.0);
                for (int i = 0; i < 3; i++)
                {
                    analogWrite(leftMotorGroup[i], motorSpeedFB);
                    analogWrite(rightMotorGroup[i], motorSpeedFB);
                }
            }
        }
    }
}
