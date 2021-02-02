#include <Wire.h>
#include "MQ135.h"
#define ANALOGPIN A8    
#define RZERO 206.85    
MQ135 gasSensor = MQ135(ANALOGPIN);
#define RLOAD 10.0
#define RZERO 76.63
#define PARA 116.6020682
#define PARB 2.769034857
int GasPin0 = A11;
int GasPin1 = A12;
int GasPin2 = A13;
int GasPin3 = A14;
int GasPin4 = A15;
int PPM1, PPM2, PPM3, PPM4, PPM5;
void setup() {
  Wire.begin(1); //슬레이브 주소                
  Wire.onRequest(requestEvent); //요청시 requestEvent함수 호출
  Wire.onReceive(receiveEvent); //데이터 전송 받을 때 receiveEvent함수 호출
  pinMode(GasPin0 ,INPUT); 
  pinMode(GasPin1 ,INPUT); 
  pinMode(GasPin2 ,INPUT); 
  pinMode(GasPin3 ,INPUT); 
  pinMode(GasPin4 ,INPUT); 
  Serial.begin(9600);           
  float rzero = gasSensor.getRZero();
}

void loop() {
   // 가스센서로부터 아날로 데이터를 받아와 시리얼 모니터로 출력함
   float rzero = gasSensor.getRZero();
   
   MQ_135();
   MQ_7_A();
   MQ_7_B_1();
   MQ_7_B_2();
   MQ_7_B_3();
   MQ_7_B_4();
   
   requestEvent();
   
}

void receiveEvent(int howMany) { //전송 데이터 읽기

  
     
      
}
void requestEvent() { //요청 시 수행 함수
  //float rzero = gasSensor.getRZero();
  //float ppm = gasSensor.getPPM();
  float ppm = gasSensor.getPPM();
  float rzero = gasSensor.getRZero();
  
  digitalWrite(13,HIGH);
  Serial.print("CO2 ppm value : ");
 // Serial.println(ppm);
 // Serial.print("MQ135 RZERO Calibration Value : ");
 // Serial.println(rzero);
  float back = rzero + ppm;
  Wire.write((int)back / 10);
  Wire.write(PPM1 / 10);  
  Wire.write(PPM2 / 10);  
  Wire.write(PPM3 / 10);  
  Wire.write(PPM4 / 10);  
  Wire.write(PPM5 / 10);  
   if(rzero / 10 > 300 || PPM1 / 10> 120){
    Serial.println("화재발생");
    if(PPM2 / 10 > 80){
      Wire.write("v");
      Serial.println("moter1 error");
    }
    else if(PPM3 / 10 > 80){
      Wire.write("m");
      Serial.println("moter2 error");
    }
    else if(PPM4 / 10 > 80){
      Wire.write("q");
      Serial.println("moter3 error");
    }
    else if(PPM5 / 10 > 80){
      Wire.write("w");
      Serial.println("moter4 error");
    }
   }
   else{
    
    Wire.write("N");
    Serial.println("감지되지않음");
   
   }
}

void MQ_7_A(){

  PPM1 = analogRead(GasPin0);
  Serial.println(analogRead(GasPin0)); // 가스센서로부터 아날로 데이터를 받아와 시리얼 모니터로 출력함
}
void MQ_7_B_1(){

  PPM2 = analogRead(GasPin1);
  Serial.println(analogRead(GasPin1)); // 가스센서로부터 아날로 데이터를 받아와 시리얼 모니터로 출력함
}
void MQ_7_B_2(){

  PPM3 = analogRead(GasPin2);
  Serial.println(analogRead(GasPin2)); // 가스센서로부터 아날로 데이터를 받아와 시리얼 모니터로 출력함
}
void MQ_7_B_3(){

  
  PPM4 = analogRead(GasPin3);
  Serial.println(analogRead(GasPin3)); // 가스센서로부터 아날로 데이터를 받아와 시리얼 모니터로 출력함
}
void MQ_7_B_4(){

  
  PPM5 = analogRead(GasPin4);
  Serial.println(analogRead(GasPin4)); // 가스센서로부터 아날로 데이터를 받아와 시리얼 모니터로 출력함
}
void MQ_135(){
  float ppm = gasSensor.getPPM();
  float rzero = gasSensor.getRZero();
  
  digitalWrite(13,HIGH);
  Serial.print("CO2 ppm value : ");
 // Serial.println(ppm);
 // Serial.print("MQ135 RZERO Calibration Value : ");
 // Serial.println(rzero);
  Serial.println(rzero + ppm);
}
