/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438

This sketch creates a fun motor party on your desk *whiirrr*
Connect a unipolar/bipolar stepper to M3/M4
Connect a DC motor to M1
Connect a hobby servo to SERVO1
*/

#include <Wire.h>
#include <Servo.h> 
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// And connect DC motors to port M1,M2,M3 and M4
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

// We'll also test out the built in Arduino Servo library
Servo servo1;


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("MMMMotor party!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Attach a servo to pin #10
  servo1.attach(10);
   
  // turn on motor M1
  myMotor1->setSpeed(200);
  myMotor1->run(RELEASE);

  // turn on motor M2
  myMotor2->setSpeed(200);
  myMotor2->run(RELEASE);

  // turn on motor M3
  myMotor3->setSpeed(200);
  myMotor3->run(RELEASE);

  // turn on motor M4
  myMotor4->setSpeed(200);
  myMotor4->run(RELEASE);  
}

int i;
void loop() {
  //  Forward Direction
  accelerateAllForward();
  slowDown_HaltAll();

  //Turn Left Or Right FORWARD
  turnLeftOrRightForward();  
  slowDown_HaltAll();

  //  Backward Direction
  deccelerateAllBackward();
  slowDown_HaltAll();
//
//  //Turn Left or Right BACKWARDS
  turnLeftOrRightBackward();
  slowDown_HaltAll();
}

//Move All Tires Forward
 void accelerateAllForward(){
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(FORWARD);
  
  for (i=0; i<255; i++) {
    servo1.write(map(i, 0, 255, 0, 180));
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i);
    myMotor4->setSpeed(i);
    delay(3);
 }
}

//Move All Tires Backward
void deccelerateAllBackward(){
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
    
    for (i=0; i<255; i++) {
      servo1.write(map(i, 0, 255, 0, 180));
      myMotor1->setSpeed(i);
      myMotor2->setSpeed(i);
      myMotor3->setSpeed(i);
      myMotor4->setSpeed(i);
      delay(3);
   }
}

// Slow all tires down to zero
void slowDown_HaltAll(){
    for (i=255; i!=0; i--) {
      servo1.write(map(i, 0, 255, 0, 180));
      myMotor1->setSpeed(i);
      myMotor2->setSpeed(i);
      myMotor3->setSpeed(i);
      myMotor4->setSpeed(i);
      delay(3);
   }
}

//Turn Tires Left or Right Forward
 void turnLeftOrRightForward(){
  myMotor1->run(FORWARD);
  myMotor4->run(FORWARD);
  
  for (i=0; i<255; i++) {
    servo1.write(map(i, 0, 255, 0, 180));
    myMotor1->setSpeed(i);
    myMotor4->setSpeed(i);
    delay(3);
 }
}

//Turn Tires Left or Right Backwards
 void turnLeftOrRightBackward(){
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  
  for (i=0; i<255; i++) {
    servo1.write(map(i, 0, 255, 0, 180));
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i);
    delay(3);
 }
}
