
#ifndef VARS_H
#define VARS_H
int driverError = 0;
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
const int MAX_BYTES = 12;     // Defines the Maximum number of bytes to be read from the serial port
char inputStream[MAX_BYTES];  // Defines the input stream for the serial port
char outputStream[MAX_BYTES]; // Defines the output stream for the serial port
// Variables for Subsystems
/*
Enable
Forwards-Backwards
Left-right

*/
bool enable = driverReady;

// Motor Directions

int motorDirection = 0;

// note: This variable is the requested motor speed
int frontLeftDP, frontRightDP, centerLeftDP, centerRightDP, rearLeftDP, rearRightDP;
int frontLeftAP, frontRightAP, centerLeftAP, centerRightAP, rearLeftAP, rearRightAP;
int frontLeftRPM, frontRightRPM, centerLeftRPM, centerRightRPM, rearLeftRPM, rearRightRPM;
int frontLeftTC, frontRightTC, centerLeftTC, centerRightTC, rearLeftTC, rearRightTC;
int motorSpeedFB, motorSpeedLR;
bool invertDirection;

// Comand stuff
String ROSString;
String Enable;
String EnableStatus;
String EN, FL, FR, CL, CR, RL, RR;
#endif