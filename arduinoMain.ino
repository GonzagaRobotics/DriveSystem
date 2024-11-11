//To Do
/*
Encoding works but in transitioning the motors to be a positive to negative range motor commands broke
1. fix motor commands: issues with negative positive values, range calculation, conversion
2. Find out expected max speed of motor to determiine optimal buffer to determine invalid values.
2. Begin implementing Track controll 
3. fix global variables
4. Integrate with hall effect sensor 

change to trac cntrl code; i.e. compare rover speed to motor speed
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
int speedFB = 0; // Forward/Backward speed (-100 to 100)
int speedLR = 0; // Left/Right speed (-100 to 100)
int trakEnable=0;
double speedMph;
double wheelCircumphrence=8; //Inches
double previousSpeeds[6]={0, 0, 0, 0, 0, 0};
double individualMotorSpeeds[6]={0,0,0,0,0,0}
int counter=0;

volatile int motorFrontLeftEncoder = 3;
volatile int motorCenterLeftEncoder = 5;
volatile int motorBackLeftEncoder = 6;
volatile int motorFrontRightEncoder = 9;
volatile int motorCenterRightEncoder = 10;
volatile int motorBackRightEncoder = 11;

void setup() {
  Serial.begin(9600);

  // Configure motor pins
  for (int i = 0; i < 3; i++) {
    pinMode(leftMotorGroup[i], OUTPUT);
    pinMode(rightMotorGroup[i], OUTPUT);
    pinMode(motorFrontLeftEncoder, INPUT);
    pinMode(motorCenterLeftEncoder, INPUT);
    pinMode(motorBackLeftEncoder, INPUT);
    pinMode(motorFrontRightEncoder, INPUT);
    pinMode(motorCenterRightEncoder, INPUT);
    pinMode(motorBackRightEncoder, INPUT);

    // Testing with Interupts, disregard
    //attachInterrupt(digitalPinToInterrupt(motorFrontLeftEncoder), encodeReading, RISING);
    //attachInterrupt(digitalPinToInterrupt(motorCenterLeftEncoder), centerLeftEncoderISR, RISING);
    //attachInterrupt(digitalPinToInterrupt(motorBackLeftEncoder), backLeftEncoderISR, RISING);
    //attachInterrupt(digitalPinToInterrupt(motorFrontRightEncoder), frontRightEncoderISR, RISING);
    //attachInterrupt(digitalPinToInterrupt(motorCenterRightEncoder), centerRightEncoderISR, RISING);
    //attachInterrupt(digitalPinToInterrupt(motorBackRightEncoder), backRightEncoderISR, RISING);


  }

  // Wait for the serial connection to initialize
  while (!Serial) {
    ; 
  }
}

void loop() {
  encodeReading();
  if (Serial.available() > 0) {
    // Read the incoming command
    String input = Serial.readStringUntil('\n');  // Read until newline

    parseCommand(input);
    motorUpdate(speedFB, speedLR);
    
  }
}

void parseCommand(String input) { //Pulls out the forard speed and left right speed 
  // Expected input format: "FB:100 LR:50 EN:1"   (At the moment EN reffers to traction Control only)

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
    String lrValue = input.substring(lrIndex + 3, lrEnd); //Check if +4 is the correct value
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

  // Constrain speeds to valid PWM range (0 to 200)
  leftSpeed = constrain(leftSpeed, 0, 200);
  rightSpeed = constrain(rightSpeed, 0, 200);
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
clock and encoder can make mistakes hense the pervious speed array,
function compares against the average previous speed to disregard any outliers, may need to tweek based on
rover speed and encoder percision

*/
void encodeReading() { 
  int encoderArray[6] = {motorFrontLeftEncoder, motorCenterLeftEncoder, motorBackLeftEncoder, motorFrontRightEncoder,motorCenterRightEncoder, motorBackRightEncoder };
  bool repeat=false;
  while(repeat==true){
    double sumSpeeds=0;
    //Testing line: allows connection of a clock to test function
    //int encoderArray[6] = {motorFrontLeftEncoder, motorFrontLeftEncoder, motorFrontLeftEncoder, motorFrontLeftEncoder,motorFrontLeftEncoder, motorFrontLeftEncoder }; 
    if(counter>=6){
      counter=0;
    }

    int i=0;
    while(i<6){
      int previousState = 0;
      int currentState = digitalRead(encoderArray[i]);

      while (currentState == previousState) {
        currentState = digitalRead(encoderArray[i]);
      }
      previousState = currentState;
      double startTime = millis();
      /* This should fix the edge detection meaning we measure the time from rising edge to falling edge instead of rising to rising
      while (currentState == previousState) {  
        currentState = digitalRead(encoderArray[i]);
      }
      previousState = currentState;
      */
      while (currentState == previousState) {
        currentState = digitalRead(encoderArray[i]);
      }
      double endTime = millis();
      double time = endTime - startTime; 
      double rpmTime = (1000.0 / time) * 60.0; 
      if (time > 0.1) { 
        double rpmTime = (1000.0 / time) * 60.0; 
        double currentSpeed = (rpmTime * (wheelCircumphrence / 12.0)) * 0.0568182;
        individualMotorSpeeds[i]=currentSpeed;
        sumSpeeds += currentSpeed; 
        i++;
      } else {
        Serial.println("Warning: Time measurement is too short or zero. Skipping calculation.");
      }
    }
    int perviousSpeed=0;
    for(int i=0; i<6; i++){
      perviousSpeed+=previousSpeeds[i];
    }
    perviousSpeed=perviousSpeed/6;
    if((sumSpeeds/6)>(perviousSpeed+30)){
      Serial.println("InvalidSpeed" + String((sumSpeeds/6), 2));
      repeat=true;
    }else{
      repeat=false;
      speedMph=sumSpeeds/6; //Average MPH speed of Rover
      previousSpeeds[counter]=speedMph;
    }
  }
  Serial.println("Current Speed is: " + String(speedMph, 2));
}
