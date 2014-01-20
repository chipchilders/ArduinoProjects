/*

This sketch is used on the sensor-side arduino, and 
communicates with the Rover sketch for the drive control
side.

*/

#include "FiniteStateMachine.h"
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Sensor Pins
const int pingPin = 3;

// Servo Pins
Servo frontServo;
int frontServoPin = 5;

// States
State stop = State(stopMotion, NULL, NULL);
State forward = State(moveForward, forwardUpdate, NULL);
State left = State(moveLeft, NULL, NULL);
State right = State(moveRight, NULL, NULL);
State backward = State(moveBackward, NULL, NULL);

// State Machine Setup
FSM motionStateMachine = FSM(stop);

// Sensor last distance
int distanceInInches = 100;

// Communication constants
const int cmdForward = 1;
const int cmdBackward = 2;
const int cmdRight = 3;
const int cmdLeft = 4;
const int cmdStop = 0;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void stopMotion()
{
    setDisplay("Stopping", NULL);
    sendMotorCommand(cmdStop);
}
void moveForward()
{
    setDisplay("Moving forward", NULL);
    sendMotorCommand(cmdForward);
}
void forwardUpdate()
{
    distanceInInches = getSingleDistance();
    if (distanceInInches<20)
    {
        setDisplay("Found obstacle in ", distanceInInches);
        stopMotion();
        delay(100);
        distanceInInches = getSingleDistance();
        if (distanceInInches<20)
        {
            setDisplay("Avoiding at ", distanceInInches);
            int direction = findPath();
            if (direction == 2) 
            {
                moveBackward();
                delay(500);
                moveRight();
                delay(600);
            }
            if (direction == 1) 
            {
                moveBackward();
                delay(500);
                moveLeft();
                delay(600);
            }
            if (direction == 0)
            {
                moveBackward();
                delay(500);
                moveRight();
                delay(1500);
            }    
            delay(500);
        }
    }
    moveForward();
}
void moveLeft()
{
    setDisplay("Turning left", NULL);
    sendMotorCommand(cmdLeft);
}
void moveRight()
{
    setDisplay("Turning right", NULL);
    sendMotorCommand(cmdRight);
}
void moveBackward()
{
    setDisplay("Moving backward", NULL);
    sendMotorCommand(cmdBackward);
}

void sendMotorCommand(byte cmd)
{
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(cmd);              // sends one byte  
    Wire.endTransmission();    // stop transmitting
}

long getSingleDistance()
{
  // Activate PING)))
  delayMicroseconds(5);
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // Get reading
  pinMode(pingPin, INPUT);
  long duration = pulseIn(pingPin, HIGH);
  long distance = duration / 74 / 2;
  return distance;
}

int findPath()
{
    int decision = 0;
    frontServo.write(40);
    delay(1000);
    long leftReading = getSingleDistance();
    frontServo.write(140);
    delay(1000);
    long rightReading = getSingleDistance();
    frontServo.write(90);
    delay(500);
    if (leftReading > rightReading + 5) decision = 1;
    if (rightReading > leftReading + 5) decision = 2;
    Serial.print("Left Reading: ");
    Serial.print(leftReading);
    Serial.print("in, Right Reading: ");
    Serial.print(rightReading);
    Serial.print("in, Using: ");
    Serial.print(decision);
    Serial.println();
    return decision;
}

void setDisplay(char status[], long value)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(status);
    if (value != NULL){
        lcd.setCursor(0, 1);
        lcd.print(value);
    }
    Serial.print(status);
    if (value != NULL)
    {
        Serial.print(" ");
        Serial.println(value);
    }
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  frontServo.attach(frontServoPin);
  frontServo.write(90);

  lcd.begin(16, 2);

  setDisplay("Starting comms", NULL);
  sendMotorCommand(cmdStop);
  delay(500);

  setDisplay("Starting in...", 3);
  delay(1000);
  setDisplay("Starting in...", 2);
  delay(1000);
  setDisplay("Starting in...", 1);
  delay(1000);
  motionStateMachine.immediateTransitionTo(forward);
}

void loop()
{
    delay(100);
    motionStateMachine.update();
}
