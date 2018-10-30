//this is slave

#include <SoftwareSerial.h>
#include <Servo.h> 

int servoPin = 3; 
Servo Servo1;
SoftwareSerial BTSerial(10, 11);
int newLine = 13; // new line character in ASCII

int angleValue = 0;
int initIndicator = 0;

const char DIRECTION = 'D';
const char MOTOR = 'M';
char action;
String value;

Servo motorESC;
int motorPin = 5;
int motorDefaultStopValue = 1400;
int motorDefaultMinValue = 1300;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(38400);
  Servo1.attach(servoPin);
  motorESC.attach(motorPin); 
}
void loop() 
{
  if(initIndicator == 0){
    initIndicator = 1;
    Servo1.write(20);
    motorESC.writeMicroseconds(motorDefaultStopValue);
  }
  
 if(BTSerial.available() > 0)
 {
    char receivedData = BTSerial.read();
    if(receivedData == DIRECTION || receivedData == MOTOR){
      action = receivedData;
    } else if (receivedData == ';') {
      manageSerialMovements();
      clearSerialActionData();
    }else{
      value += receivedData;
    }
 }
}

void manageSerialMovements() {
  int valueNumeric = value.toInt();

  if (action == DIRECTION) {
    moveDirection(valueNumeric);
  } else if(action == MOTOR){
    moveMotor(valueNumeric);
  }
}

void moveDirection(int angleValue)
{
  Servo1.write(angleValue);
}

int lastMotorValue = 0;
void moveMotor(int motorValue)
{
  if(lastMotorValue != motorValue){
    lastMotorValue = motorValue;
    int value = 0;
    if(motorValue > 0){
      value = motorDefaultMinValue - motorValue * 10;
    }
    Serial.println(value);
    motorESC.writeMicroseconds(value);
  }
}

/*
   Vide les valeurs de la communication serie de l'action
*/
void clearSerialActionData() {
  value = "";
  action = -1;
}
