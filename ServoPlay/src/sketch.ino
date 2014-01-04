// Sweep
// by BARRAGAN  

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

int sensorPin = 0;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor
float servoTarget = 0;
float servoRawTarget = 0;

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{
  sensorValue = analogRead(sensorPin)+1;
  servoTarget = (sensorValue/1024)*180;
  Serial.println(servoTarget);
  myservo.write(servoTarget);
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
