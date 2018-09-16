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

#define trigPin 10
#define echoPin 13

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
  Serial.println("Autonomous Motion Using UltraSonic Sensor!");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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
  //Set servo position to 90 degrees (centered)
  //servo1.write(90);
  //delay(1000);
  
  //  Initiate Sensor Reading
  float distance = takeSensorReading();
      
  while(distance > 50){
    //  Accelerate in Forward Direction
    deccelerateAllBackward();

    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);

    //Take reading
    distance = takeSensorReading();
  }

  //Halt all wheels  
  haltAllWheels();
  
  //Turn servo 90 degress clockwise 
  turnServo90AntiClockwise();
  
  //Take reading
  distance = takeSensorReading();
  
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);

  if(distance > 50){
    //Turn Right FORWARD
    turnRightBackward();
    delay(1000);

    // Halt wheels
    haltAllWheels();

    //Return servo to initial position
    turnServo90Clockwise();
    delay(1000);
  }else{
    //Return servo to initial position
    turnServo90Clockwise();

    //Take reading
    distance = takeSensorReading();
  }
}

//Move All Tires Forward
 void accelerateAllForward(){
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(FORWARD);
  
  myMotor1->setSpeed(200);
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(200);
  myMotor4->setSpeed(200);
    
}

//Move All Tires Backward
void deccelerateAllBackward(){
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);
    
    myMotor1->setSpeed(200);
    myMotor2->setSpeed(200);
    myMotor3->setSpeed(200);
    myMotor4->setSpeed(200);
      
}

// Slow all tires down to zero
void haltAllWheels(){  
    myMotor1->setSpeed(0);
    myMotor2->setSpeed(0);
    myMotor3->setSpeed(0);
    myMotor4->setSpeed(0);
}

//Turn Tires Left or Right Forward
 void turnLeftOrRightForward(){
  myMotor1->run(FORWARD);
  myMotor4->run(FORWARD);
    
  myMotor1->setSpeed(175);
  myMotor4->setSpeed(175);
}

//Turn Tires Left Backwards
 void turnLeftBackward(){
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  
  myMotor2->setSpeed(175);
  myMotor3->setSpeed(175);
}

//Turn Tires Right Backwards
 void turnRightBackward(){
  myMotor1->run(BACKWARD);
  myMotor4->run(BACKWARD);
  
  myMotor1->setSpeed(175);
  myMotor4->setSpeed(175);
}

void turnServo90Clockwise(){
  for(int pos = 0; pos <= 90; pos += 1){
    servo1.write(pos);
    delay(15);
  }
}

void turnServo90AntiClockwise(){
  for(int pos = 90; pos >= 0; pos -= 1){
    servo1.write(pos);
    delay(15);
  }
}

float takeSensorReading(){
  float duration, distance;
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  return distance;
}

