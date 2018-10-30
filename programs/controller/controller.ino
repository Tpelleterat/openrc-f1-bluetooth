//this is master

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);

int lastAngleValue;
int lastMotorValue;

void setup() 
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  //Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop()
{
  String message = "";
  message += getAngleMessage();
  message += getMotorMessage();

  if(message != ""){
    BTSerial.println(message);
  }
  delay(50);
}

String getAngleMessage(){
  String message = "";
  int angleValue = calcAngleValue();
  
  if(lastAngleValue != angleValue){
    lastAngleValue = angleValue;
    
    message += "D";
    if(angleValue < 10){
      message += "0";
    }
    message += angleValue;
    message += ";";
  
  }
  return message;
}

String getMotorMessage(){
  String message = "";
  int motoValue = calcMotorValue();

  if(lastMotorValue != motoValue){
    lastMotorValue = motoValue;
    
    message += "M";
    if(motoValue < 10){
      message += "0";
    }
    message += motoValue;
    message += ";";
  }
  
  return message;
}

int calcAngleValue() {
  int value = analogRead(A0);
  
  if(value < 502){
    return value * 0.04;
  }else if(value > 1011){
    return 40;
  }else if(value > 509){
    int valBuild = value - 501;
    return (valBuild * 0.04) + 20;
  }
  
  return 20;
}

int calcMotorValue() {
  int value = analogRead(A1);

  if(value < 502){
    return 0;
  }else if(value > 1011){
    return 10;
  }else if(value > 509){
    int valBuild = value - 501;
    return (valBuild * 0.02);
  }
  
  return 0;
}
