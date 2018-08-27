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

char data = 0;            //Variable for storing received data
void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission
    Serial.print("\nAutonomous and Manual drive Using Bluetooth!\n");                    

    AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
   
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
void loop()
{
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");
      
      if(data == '1'){              // Checks whether value of data is equal to 1
          Serial.print("Autonomous drive");
          Serial.print("\n");
          accelerateAllForward();
      }else if(data == '0'){         //  Checks whether value of data is equal to 0
         Serial.print("Manual drive");
         Serial.print("\n");
         haltAllWheels();
      }
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

//Turn Tires Left or Right Backwards
 void turnLeftOrRightBackward(){
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  
  myMotor2->setSpeed(175);
  myMotor3->setSpeed(175);
}
