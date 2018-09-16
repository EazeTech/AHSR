/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

// Declare the Servo pin
int servoPin = 9; 
 
void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on declared pin
} 
 
void loop() 
{
    myservo.write(0);
    delay(1000);
                                  
    myservo.write(90);
    delay(1000);

    myservo.write(180);
    delay(1000);

} 

