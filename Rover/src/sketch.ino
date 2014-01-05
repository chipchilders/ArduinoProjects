//. Motor driver shield- 2012 Copyright (c) Seeed Technology Inc.
// 
//  Original Author: Jimbo.we
//  Contribution: LG
//  
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

int pinI1=8;//define I1 interface
int pinI2=11;//define I2 interface 
int speedpinA=9;//enable motor A
int pinI3=12;//define I3 interface 
int pinI4=13;//define I4 interface 
int speedpinB=10;//enable motor B
int spead =255;//define the spead of motor
int turnspeed =255;
 
void setup()
{
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
}
 
void forward()
{
     analogWrite(speedpinB,spead);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
}
void backward()
{
     analogWrite(speedpinB,spead);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
}
void left()
{
     analogWrite(speedpinA,turnspeed);//input a simulation value to set the speed
     digitalWrite(pinI2,LOW);//turn DC Motor A move clockwise
     digitalWrite(pinI1,HIGH);
}
void right()
{
     analogWrite(speedpinA,spead);//input a simulation value to set the speed
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}
void stop()
{
     digitalWrite(speedpinA,LOW);// Unenble the pin, to stop the motor. this should be done to avid damaging the motor. 
     digitalWrite(speedpinB,LOW);
     delay(1000);
}

void loop()
{
  stop();
  delay(2000);

  left();
  forward();
  delay(2000);

  stop();
  delay(2000);

  right();
  backward();
  delay(2000);

  stop();
  delay(2000);
}