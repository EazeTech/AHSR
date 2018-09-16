// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h> 

// DC motors M1 & M2
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

// DC hobby servos
Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
  
  // turn on servos
  servo1.attach(10);
  servo2.attach(9);
   
  // turn on motors
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

int i;

// Test the DC motors and servos ALL AT ONCE!
void loop() {
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
  for (i=0; i<255; i++) {
    servo1.write(i);
    servo2.write(i);
    
    motor1.setSpeed(i);
    motor2.setSpeed(i);   
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo1.write(i-255);
    servo2.write(i-255);
    
    motor1.setSpeed(i);
    motor2.setSpeed(i);   
    delay(3);
 }
 
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  
  for (i=0; i<255; i++) {
    servo1.write(i);
    servo2.write(i);
    
    motor1.setSpeed(i);
    motor2.setSpeed(i); 
    
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo1.write(i-255);
    servo2.write(i-255);
    
    motor1.setSpeed(i);  
    motor2.setSpeed(i); 
    
    delay(3);
  }
}
