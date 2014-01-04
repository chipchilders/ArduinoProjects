// Sweep
// by BARRAGAN  

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

int sensorPin = 0;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor
float servoTarget = 0;
int lastServoTarget = 0;

// LED leads connected to PWM pins
const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;
const int VERYBLUE_LED_PIN = 2;

// Used to store the current intensity level of the individual LEDs
int redIntensity = 0;
int greenIntensity = 0;
int blueIntensity = 0;

// Length of time we spend showing each color
const int DISPLAY_TIME = 100; // In milliseconds

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
  pinMode(VERYBLUE_LED_PIN,OUTPUT);
}

void blinkblue(int count){
  for (int i=0; i<count; i++){
    digitalWrite(VERYBLUE_LED_PIN, HIGH);
    delay(DISPLAY_TIME);
    digitalWrite(VERYBLUE_LED_PIN, LOW);
    delay(DISPLAY_TIME);
  }
} 

void loop()
{
  sensorValue = analogRead(sensorPin);
  servoTarget = (sensorValue/1024)*180;
  Serial.println(servoTarget);
  myservo.write(servoTarget);
  if (lastServoTarget != int(servoTarget)){
    blinkblue(1);
  }
  lastServoTarget = servoTarget;
  delay(15);


  /* 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  */
} 
