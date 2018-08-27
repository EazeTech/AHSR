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
char data = 0;            //Variable for storing received data

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.print("\nAutonomous and Manual drive Using Bluetooth!\n");
  
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
//  if(Serial.available() > 0){      // Send data only when you receive data:
//      Serial.print("\nBluetooth Connected\n");
//      data = Serial.read();        //Read the incoming data & store into data
//      Serial.print("\nInput Request: ");
//      Serial.print(data);          //Print Value inside data in Serial monitor
//      Serial.print("\n");
//      
//      if(data == 'a'){
//        Serial.print("Auto drive\n");
//        autoDrive();
//      }else{
//         Serial.print("Manual drive\n");
//         manualDrive();
//      }
//   }else{
      //if no input stream default to Autonomous drive
      
      autoDrive();
      //Serial.print("\nLooping..\n");
//   }
}

//MY CUSTOM METHODS

void manualDrive(){
  haltAllWheels();
  data = Serial.read();        //Read the incoming data & store into data
  Serial.print(data);
  Serial.print("\n");
  
  while(data != 'a'){
      if(data == 'f'){
        haltAllWheels();
        Serial.print(data);
        Serial.print("\nAccelerate\n");
        
        accelerateAll();
      }else if(data == 'b'){
        haltAllWheels();
        Serial.print(data);
        Serial.print("\nDecelerate\n");
        
        deccelerateAll();
      }else if(data == 'l'){
        haltAllWheels();
        Serial.print(data);
        Serial.print("\nTurning Left...\n");
        
        turnLeftForward();
        //Then Accelerate
        accelerateAll();
        Serial.print("\nDone Turning!\n");
      }else if(data == 'r'){
        haltAllWheels();
        Serial.print(data);
        Serial.print("\nTurning Right...\n");
        
        turnRightForward();
        //Then Accelerate        
        accelerateAll();
        Serial.print("\nDone Turning!\n");
      }else if(data == '0'){
        Serial.print(data);
        Serial.print("\nBrake Applied\n");
        haltAllWheels();
      }

      data = Serial.read();        //Read the incoming data & store into data
   }
}

void autoDrive(){

  //  Initiate Sensor Reading
  float distance = takeSensorReading();
  int servo_position = 80;
  
  //Reset Servo & U-sensor to Forward Position
  servo1.write(servo_position);

  if(distance <= 50)
    lookAround(servo_position);
      
  while(distance > 50){
    //  Accelerate in Forward Direction
    accelerateAll();

    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
       
    Serial.print("\nInput Request: ");
    Serial.print(data);          //Print Value inside data in Serial monitor
    Serial.print("\n");

    //Take reading
    distance = takeSensorReading();
    
    //Read the incoming data & store into data
    data = Serial.read();

    //Exit Loop to Manual Override    
    if(data == 'm')
      manualDrive();
  }

  lookAround(servo_position);
}

//Move All Tires Forward
 void accelerateAll(){
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(FORWARD);
  
  myMotor1->setSpeed(255);
  myMotor2->setSpeed(255);
  myMotor3->setSpeed(255);
  myMotor4->setSpeed(255);
    
}

//Move All Tires Backward
void deccelerateAll(){
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

//Turn Right Backward
 void turnRightBackward(){
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
    
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(200);

  delay(1600);
    
  // Halt wheels
  haltAllWheels();
}

//Turn Left Backward
 void turnLeftBackward(){
  myMotor1->run(BACKWARD);
  myMotor4->run(BACKWARD);
    
  myMotor1->setSpeed(200);
  myMotor4->setSpeed(200);

  delay(1600);
    
  // Halt wheels
  haltAllWheels();
}

//Turn Right Forward
 void turnRightForward(){
  myMotor1->run(BACKWARD);
  myMotor4->run(BACKWARD);
  
  myMotor1->setSpeed(200);
  myMotor4->setSpeed(200);

  delay(1600);
    
  // Halt wheels
  haltAllWheels();
}

//Turn Left Forward
 void turnLeftForward(){
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(200);

  delay(1600);
    
  // Halt wheels
  haltAllWheels();
}

// Turn U-Sensor Clockwise
void turnServo90Clockwise(int   pos){
  while(pos <= 180){
    servo1.write(pos);
    delay(15);
    pos += 1;
  }
}

// Turn U-Sensor Anti-Clockwise
void turnServo90AntiClockwise(int pos){
  while(pos >= 0){
    servo1.write(pos);
    delay(15);
    pos -= 1;
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
  distance = (duration / 2) * 0.0344 - 3;

  return distance;
}


void lookAround(int serv_pos){

  //Halt all wheels  
  haltAllWheels();
  
  //Turn servo 90 degress clockwise 
  turnServo90AntiClockwise(serv_pos);
  
  //Take reading
  int distance = takeSensorReading();
  
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);

  if(distance > 50){
    //Turn Right FORWARD
    turnRightForward();
  }else{
    //Return servo to initial position
    turnServo90Clockwise(serv_pos);

    //Take reading
    distance = takeSensorReading();
    
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);

    if(distance > 50){
       //Turn Right FORWARD
      turnLeftForward();
    }else{
      //Face Forward
      servo1.write(serv_pos);
      delay(1000);
      
      //Take reading
      int distance = takeSensorReading();
     
      if(distance <= 50){
        // Turn Right Back
         turnRightBackward();
      }
    }
  }
}


