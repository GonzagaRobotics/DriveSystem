#include "Depends/vars.h"
void initializeMotorDriver()
{ // Define the motor pins
    int motorFrontLeft = 1;
    int motorCenterLeft = 2;
    int motorBackLeft = 3;
    int motorFrontRight = 4;
    int motorCenterRight = 5;
    int motorBackRight = 6;
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
        analogWrite(leftMotorGroup[i], LOW);
        analogWrite(rightMotorGroup[i], LOW);
    }
    // Set the driver ready flag to 1
    driverReady = 1;
}

void motorDriver()
{
    // TODO: Add motor driver code
    // Cordinate with Damon on the best method for implementing this
    // This is a placeholder
}
