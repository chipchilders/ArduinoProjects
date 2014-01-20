#include "FiniteStateMachine.h"
#include <Wire.h>

// Turning Motor Pins
const int pinI1=8;//define I1 interface
const int pinI2=11;//define I2 interface 
const int speedpinA=9;//enable motor A

// Drive Motor Pins
const int pinI3=12;//define I3 interface 
const int pinI4=13;//define I4 interface 
const int speedpinB=10;//enable motor B

// Motor speed settings
const int speed = 254;

// States
State stop = State(stopMotion, NULL, NULL);
State forward = State(moveForward, NULL, NULL);
State left = State(moveLeft, NULL, NULL);
State right = State(moveRight, NULL, NULL);
State backward = State(moveBackward, NULL, NULL);

// State Machine Setup
FSM motionStateMachine = FSM(stop);

// Communication constants
const int cmdForward = 1;
const int cmdBackward = 2;
const int cmdRight = 3;
const int cmdLeft = 4;
const int cmdStop = 0;

void stopMotion()
{
    Serial.println("Stopping");
    haltLeftMotors();
    haltRightMotors();
}
void moveForward()
{
    Serial.println("Moving forward");
    forwardLeftMotors();
    forwardRightMotors();
}
void moveLeft()
{
    Serial.println("Moving left");
    forwardRightMotors();
    backwardLeftMotors();
}
void moveRight()
{
    Serial.println("Moving right");
    forwardLeftMotors();
    backwardRightMotors();
}
void moveBackward()
{
    Serial.println("Moving backward");
    backwardRightMotors();
    backwardLeftMotors();
}


// Specific Motor Controls
//// Left Motor Control
void haltLeftMotors()
{
    analogWrite(speedpinA,speed);
    digitalWrite(pinI2,LOW);
    digitalWrite(pinI1,LOW);
}

void forwardLeftMotors()
{
    analogWrite(speedpinA,speed);
    digitalWrite(pinI2,LOW);
    digitalWrite(pinI1,HIGH);
}

void backwardLeftMotors()
{
    analogWrite(speedpinA,speed);
    digitalWrite(pinI2,HIGH);
    digitalWrite(pinI1,LOW);
}

//// Right Motor Control
void haltRightMotors()
{
    analogWrite(speedpinB, 0);
    digitalWrite(pinI4,LOW);
    digitalWrite(pinI4,LOW);
    delay(50);
}

void forwardRightMotors()
{
    analogWrite(speedpinB,speed);
    digitalWrite(pinI4,HIGH);
    digitalWrite(pinI3,LOW);
    delay(50);
}

void backwardRightMotors()
{
    analogWrite(speedpinB,speed);
    digitalWrite(pinI4,LOW);
    digitalWrite(pinI3,HIGH);
    delay(50);
}

void setup()
{

  // Setup turning motor pins
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);

  // Setup drive motor pins
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);

  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

}

void loop()
{
    delay(100);
}

void receiveEvent(int howMany)
{
    Serial.println("got one!");
  char action;

  while(0 < Wire.available()) // loop through all but the last
  {
    action = Wire.read(); // receive byte as a character
    switch (action) {
        case cmdForward:
            motionStateMachine.immediateTransitionTo(forward);
            break;
        case cmdBackward:
            motionStateMachine.immediateTransitionTo(backward);
            break;
        case cmdRight:
            motionStateMachine.immediateTransitionTo(right);
            break;
        case cmdLeft:
            motionStateMachine.immediateTransitionTo(left);
            break;
        default:
            motionStateMachine.immediateTransitionTo(stop);
    }
  }
}
