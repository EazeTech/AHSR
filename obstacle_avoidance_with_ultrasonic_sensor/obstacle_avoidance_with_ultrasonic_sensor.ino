#include <AFMotor.h>


AF_DCMotor motor1(1); // set up motor1. motor1 is the name, and (1) is the port
AF_DCMotor motor2(2); // set up motor2. motor2 is the name, and (2) is the port
#define trigPin 7 // define the pins of your sensor
#define echoPin 6

void setup() {
  motor1.setSpeed(255); //set the speed of the motors, between 0-255
  motor2.setSpeed (255);
  
  Serial.begin(9600); // begin serial communitication
  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)
}

void loop() {
  long distance;
  distance = takeSensorReading();
  
  delay (50);

  // Move robot forward  
  moveForward();
  
  
  if (distance < 10)/*if there's an obstacle 10 centimers, ahead, do the following: */ {
  
    Serial.print (distance);
    Serial.print ("cm");
    
    //Turn robot right
    turnRight();

  }
}

void moveForward(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);

  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void moveBackward(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
}

void turnLeft(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
}

void turnRight(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);

  motor1.setSpeed(200);
  motor2.setSpeed(200);
}

void stopMotion(){  
    motor1.setSpeed(0);
    motor2.setSpeed(0);
}

long takeSensorReading(){
  long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // delays are required for a successful sensor operation.
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  return (duration/2) / 58.2;// convert the distance to centimeters. 29.1
}

