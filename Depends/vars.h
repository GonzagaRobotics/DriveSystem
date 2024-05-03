#ifndef VARS_H
#define VARS_H

int driverReady = 0;

// Motor Groups
int motorFrontLeft;
int motorCenterLeft;
int motorBackLeft;
int motorFrontRight;
int motorCenterRight;
int motorBackRight;
// Motor Arrays

int leftMotorGroup[3];
int rightMotorGroup[3];

// Serial Stuff
const int MAX_BYTES = 20;    // Defines the Maximum number of bytes to be read from the serial port
char inputStream[MAX_BYTES]; // Defines the input stream for the serial port
// Variables for Subsystems
/*
Enable
Forwards-Backwards
Left-right

*/
bool enable = driverReady;
int directionForward = 0;
int directionBackward = 0;
int directionLeft = 0;
int directionRight = 0;
#endif