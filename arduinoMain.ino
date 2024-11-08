//To Do
/*
1. Test encoder module
2. Update python test code to test other modules
3. basic imlementation of trac contorl



*/
#include "init.h"


#include <Arduino.h>


// Motor pins
int motorFrontLeft = 3;
int motorCenterLeft = 5;
int motorBackLeft = 6;
int motorFrontRight = 9;
int motorCenterRight = 10;
int motorBackRight = 11;

// Motor groups
int leftMotorGroup[3] = {motorFrontLeft, motorCenterLeft, motorBackLeft};
int rightMotorGroup[3] = {motorFrontRight, motorCenterRight, motorBackRight};

// Speeds
int speedFB = 0; // Forward/Backward speed (-100 to 100)
int speedLR = 0; // Left/Right speed (-100 to 100)
int trakEnable=0;
double speedMph;
double wheelCircumphrence=8; //Inches


int motorFrontLeftEncoder = 3;
int motorCenterLeftEncoder = 5;
int motorBackLeftEncoder = 6;
int motorFrontRightEncoder = 9;
int motorCenterRightEncoder = 10;
int motorBackRightEncoder = 11;

pinMode(motorFrontLeftEncoder, INPUT);
pinMode(motorCenterLeftEncoder, INPUT);
pinMode(motorBackLeftEncoder, INPUT);
pinMode(motorFrontRightEncoder, INPUT);
pinMode(motorCenterRightEncoder, INPUT);
pinMode(motorBackRightEncoder, INPUT);


void setup() {
  Serial.begin(9600);

  // Configure motor pins
  for (int i = 0; i < 3; i++) {
    pinMode(leftMotorGroup[i], OUTPUT);
    pinMode(rightMotorGroup[i], OUTPUT);
  }

  // Wait for the serial connection to initialize
  while (!Serial) {
    ; 
  }
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming command
    String input = Serial.readStringUntil('\n');  // Read until newline

    parseCommand(input);
    motorUpdate(speedFB, speedLR);
  }
}

void parseCommand(String input) { //Pulls out the forard speed and left right speed 
  // Expected input format: "FB:100 LR:-50 EN:1"   (At the moment EN reffers to traction Control only)

  int fbIndex = input.indexOf("FB:");
  int lrIndex = input.indexOf("LR:");
  int enIndex = input.indexOf("EN:");

  if (fbIndex != -1) {
    int fbEnd = input.indexOf(' ', fbIndex);
    if (fbEnd == -1) fbEnd = input.length();
    String fbValue = input.substring(fbIndex + 3, fbEnd);
    speedFB = fbValue.toInt();
  }

  if (lrIndex != -1) {
    int lrEnd = input.indexOf(' ', lrIndex);
    if (lrEnd == -1) lrEnd = input.length();
    String lrValue = input.substring(lrIndex + 3, lrEnd);
    speedLR = lrValue.toInt();
  }

  if (enIndex != -1) {
    int enEnd = input.indexOf(' ', enIndex);
    if (enEnd == -1) enEnd = input.length();
    String enValue = input.substring(enIndex + 3, enEnd);
    trakEnable = enValue.toInt();
  }

} 

void motorUpdate(int speedFB, int speedLR) {
  double leftSpeed = speedFB + speedLR;
  double rightSpeed = speedFB - speedLR;

  // Constrain speeds to valid PWM range (-100 to 100)
  leftSpeed = constrain(leftSpeed, -100, 100);
  rightSpeed = constrain(rightSpeed, -100, 100);
  leftSpeed=1/leftSpeed;
  rightSpeed=1/rightSpeed;
  // Set motor speeds
  setMotorSpeed(leftMotorGroup, leftSpeed);
  setMotorSpeed(rightMotorGroup, rightSpeed);

  //debugging
  Serial.print("Left Speed: ");
  Serial.print(leftSpeed);
  Serial.print(" Right Speed: ");
  Serial.println(rightSpeed);
}

void setMotorSpeed(int motorPins[], int speed) {
  int pwmValue = abs(speed);

  for (int i = 0; i < 3; i++) {
    analogWrite(motorPins[i], pwmValue);
  }
}

void motorStop() { //Stops the Motor
  for (int i = 0; i < 3; i++) {
    analogWrite(leftMotorGroup[i], 0);
    analogWrite(rightMotorGroup[i], 0);
  }
  Serial.println("Motors Stopped");
}

void trackCntrl() {
  if(trackCntrl!=1){
    return 0;
  }
  // Placeholder for traction control code
  //

}

/*
Untested module
Test on one moror encoder with button later
implement For loop and average out individual Moror speeds for more acurate overall speed value
Test with one before implementing
*/
void encodeReading(){//UNTESTED Only works for one Moror so far
  int encoderState=0;
  encoderState= digitalRead(motorFrontLeftEncoder);
  double speedMph;
  double startTime=0;
  double endTime;
  double time;
  double rpmTime;
  while(encoderState!=1){ //Fix this test with arduino
    encoderState= digitalRead(motorFrontLeftEncoder);
  }
  read[i]=millis();
  StartTime=millis();
  delay(1); // test dellay
  while(encoderState!=1){
    encoderState= digitalRead(motorFrontLeftEncoder);
  }
  endTime=millis();
  time=endTime-startTime;
  rpmTime=time*6;
  speedMph= (rpmTime*(63360/wheelCircumphrence))*(3600000);
}