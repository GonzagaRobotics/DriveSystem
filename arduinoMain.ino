//To Do
/*
1. add traction toggle 
2. 
3. Test and fix encoder Read Function
4. Split into multiple files
5. Fix values for the motors tallon SRX ensure speed runs right
    Might be -1 to 1



*/


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
int speedFB = 0; // Forward/Backward speed (-255 to 255)
int speedLR = 0; // Left/Right speed (-255 to 255)
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
  // Expected input format: "FB:100 LR:-50"
  int fbIndex = input.indexOf("FB:");
  int lrIndex = input.indexOf("LR:");

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
} 

void motorUpdate(int speedFB, int speedLR) {
  int leftSpeed = speedFB + speedLR;
  int rightSpeed = speedFB - speedLR;

  // Constrain speeds to valid PWM range (-255 to 255)
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

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