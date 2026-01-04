#include <Arduino.h>
#include <ArduinoJson.h>

const int numMotors = 6;
// TODO: Actual pin assignments
const int motorFL = 0;
const int motorFR = 0;
const int motorCL = 0;
const int motorCR = 0;
const int motorRL = 0;
const int motorRR = 0;
const int motorPins[numMotors] = {motorFL, motorFR, motorCL, motorCR, motorRL, motorRR};

JsonDocument doc;
unsigned long lastCmdTime = 0;
int motorCmds[numMotors] = {0, 0, 0, 0, 0, 0};

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < numMotors; i++)
  {
    pinMode(motorPins[i], OUTPUT);
  }

  while (!Serial)
  {
  }
}

void loop()
{
  // Read incoming serial data
  while (Serial.available() > 0)
  {
    DeserializationError error = deserializeJson(doc, Serial);

    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    lastCmdTime = millis();
    for (int i = 0; i < numMotors; i++)
    {
      motorCmds[i] = doc["motors"][i];
    }
  }

  // As an extra safety measure, stop all motors if no command is received for 500 ms
  if (millis() - lastCmdTime > 500)
  {
    for (int i = 0; i < numMotors; i++)
    {
      motorCmds[i] = 0;
    }
  }

  for (int i = 0; i < numMotors; i++)
  {
    analogWrite(motorPins[i], motorCmds[i]);
  }

  delay(20);
}
