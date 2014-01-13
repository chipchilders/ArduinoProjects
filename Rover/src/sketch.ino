#include "FiniteStateMachine.h"

// Turning Motor Pins
const int pinI1=8;//define I1 interface
const int pinI2=11;//define I2 interface 
const int speedpinA=9;//enable motor A

// Drive Motor Pins
const int pinI3=12;//define I3 interface 
const int pinI4=13;//define I4 interface 
const int speedpinB=10;//enable motor B

// Motor speed settings
const int spead =255;
const int turnspeed =255;

// Sensor Pins
const int pingPin = 3;

// States
State stop = State(stopMotion, NULL, NULL);
State forward = State(moveForward, forwardUpdate, NULL);
State leftForward = State(moveLeft, NULL, NULL);
State rightForward = State(moveRight, NULL, NULL);
State backward = State(moveBackward, NULL, NULL);
State leftBackward = State(moveBackLeft, backwardUpdate, NULL);
State rightBackward = State(moveBackRight, NULL, NULL);

// State Machine Setup
FSM motionStateMachine = FSM(stop);

// Sensor last distance
int distanceInInches = 100;

void stopMotion()
{
    straightenTurningMotor();
    haltDriveMotor();
}
void moveForward()
{
    Serial.println("Transitioning to forward");
    forwardDriveMotor();
    straightenTurningMotor();
}
void forwardUpdate()
{
    if (distanceInInches<10)
    {
        motionStateMachine.transitionTo(leftBackward);
        Serial.println("Please transition to backward");
    }
}
void moveLeft()
{
    forwardDriveMotor();
    leftTurningMotor();
}
void moveRight()
{
    forwardDriveMotor();
    rightTurningMotor();
}
void moveBackward()
{
    backwardDriveMotor();
    straightenTurningMotor();
}
void moveBackLeft()
{
    Serial.println("Transitioning to leftBackward");
    backwardDriveMotor();
    rightTurningMotor();
}
void moveBackRight()
{
    backwardDriveMotor();
    leftTurningMotor();
}
void backwardUpdate()
{
    if (distanceInInches>30)
    {
        motionStateMachine.transitionTo(forward);
        Serial.println("Please transition to forward.");
    }
}
// Specific Motor Controls

//// Turning Motor Control
void straightenTurningMotor()
{
    analogWrite(speedpinA,spead);
    digitalWrite(pinI2,LOW);
    digitalWrite(pinI1,LOW);
}

void leftTurningMotor()
{
    analogWrite(speedpinA,spead);
    digitalWrite(pinI2,LOW);
    digitalWrite(pinI1,HIGH);
}

void rightTurningMotor()
{
    analogWrite(speedpinA,spead);
    digitalWrite(pinI2,HIGH);
    digitalWrite(pinI1,LOW);
}

//// Drive Motor Control
void haltDriveMotor()
{
    analogWrite(speedpinB, 0);
    digitalWrite(pinI4,LOW);
    digitalWrite(pinI4,LOW);
    delay(50);
}

void forwardDriveMotor()
{
    analogWrite(speedpinB,spead);
    digitalWrite(pinI4,HIGH);
    digitalWrite(pinI3,LOW);
    delay(50);
}

void backwardDriveMotor()
{
    analogWrite(speedpinB,spead);
    digitalWrite(pinI4,LOW);
    digitalWrite(pinI3,HIGH);
    delay(50);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
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

  pinMode(pingPin, INPUT);
  long duration = pulseIn(pingPin, HIGH);

  return microsecondsToInches(duration);
}

long frontDistance()
{

  long firstReading = getSingleDistance();
  long secondReading = getSingleDistance();
  long averageReading = (firstReading+secondReading)/2;
  Serial.print("First Reading: ");
  Serial.print(firstReading);
  Serial.print("in, Second Reading: ");
  Serial.print(secondReading);
  Serial.print("in, Using: ");
  Serial.print(averageReading);
  Serial.print("in.");
  Serial.println();
  return averageReading;
}

void setup()
{
  Serial.begin(9600);

  // Setup turning motor pins
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);

  // Setup drive motor pins
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);

  delay(5000);

  motionStateMachine.transitionTo(forward);
  motionStateMachine.update();
}

void loop()
{
  distanceInInches = frontDistance();
  Serial.print("Distance: ");
  Serial.print(distanceInInches);
  Serial.println();
  motionStateMachine.update();
}
