#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>

// joystick
#define joyX A1
#define joyY A2

Servo servoX;  // create servo object to control a servo
Servo servoY;
float posX = 0;    // variable to store the servo position
float posY = 0;

MPU6050 mpu(Wire);
unsigned long timer = 0;

int joyX_zero = -1;
int joyY_zero = -1;
int joy_offset = 50;

void setup() {

  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  servoX.attach(4);  // attaches the servo on pin 9 to the servo object
  servoX.write(90);
  servoY.attach(3);  // attaches the servo on pin 9 to the servo object
  servoY.write(90);
  
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");

  joyX_zero = analogRead(joyX);
  joyY_zero = analogRead(joyY);
}


void loop() {
  mpu.update();

  /*
  if((millis()-timer)>10){ // print data every 10ms
  Serial.print("X : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tY : ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tZ : ");
  Serial.println(mpu.getAngleZ());
  timer = millis();  
  }*/
Serial.println("jox:");
Serial.println(analogRead(joyX));
Serial.println("joy:");
Serial.println(analogRead(joyY));
Serial.println("zero start");
    Serial.println(joyY_zero);
    Serial.println(joyY_zero);
Serial.println("zero end");

  while (!(analogRead(joyX) > (joyY_zero - joy_offset) && analogRead(joyX) < (joyY_zero + joy_offset)) || !(analogRead(joyY) > (joyY_zero - joy_offset) && analogRead(joyY) < (joyY_zero + joy_offset)))
  {
    posX = analogRead(joyX) / 5.688888888888889;
    posY = analogRead(joyY) / 5.688888888888889; 
    servoX.write(posX);
    servoY.write(posY);  
    Serial.println(posX);
    Serial.println(posY);
  }
  
  servoX.write(2*mpu.getAngleX() + 90);
  servoY.write((180 - (2*mpu.getAngleY() + 90)));   
  

}
