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
    // TODO: CHANGE PIN NUMBERS

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
    // CHANGEME

        for (int i = 0; i < 3; i++)
    {
        analogWrite(leftMotorGroup[i], moveLeftMotor);
        analogWrite(rightMotorGroup[i], moveRightMotor);
    }
}
