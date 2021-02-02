#include <Wire.h>
void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Wire.begin();
  Serial.begin(9600); 
}

byte x = 0;

void loop() {
  Wire.beginTransmission(1);

   //슬레이브(1)에 4byte 요청
  Wire.endTransmission();
  delay(500);


  Wire.requestFrom(1, 7);
  while (Wire.available()) {
    Serial.print("MQ135 : ");
    int g = Wire.read(); 
    Serial.println(g);
    Serial.print("MQ7_1 : ");
    int h = Wire.read(); 
    Serial.println(h);
    Serial.print("MQ7_2 : ");
    int j = Wire.read(); 
    Serial.println(j);
    Serial.print("MQ7_3 : ");
    int k = Wire.read(); 
    Serial.println(k);
    Serial.print("MQ7_4 : ");
    int p = Wire.read(); 
    Serial.println(p);
    Serial.print("MQ7_5 : ");
    int o = Wire.read(); 
    Serial.println(o);
    Serial.print("메세지 : ");
    char d= Wire.read();
    if(d == 'v'){
      analogWrite(3, 0);
      Serial.println("moter1 down");
    }
    else if(d == 'm'){
      analogWrite(9, 0);
      Serial.println("moter2 down");
    }
    else if(d == 'q'){
      analogWrite(5, 0);
      Serial.println("moter3 down");
    }
    else if(d == 'w'){

      analogWrite(6, 0);
      Serial.println("moter4 down");
    }
    else if(d == 'N'){
      Serial.println("감지되지않음");


  }
  else if(d == 's'){
    Serial.println("모터정상작동");
    help_a();
  }

  x++;
  if(x==6)x=0;
}
}
void help_a(){
    digitalWrite(7, LOW);      // Motor A 방향설정1
    digitalWrite(8, HIGH);     // Motor A 방향설정2
    analogWrite(9, 255);      // Motor A 속도조절 (0~255)
          /모터B설정/
    digitalWrite(4, HIGH);    // Motor B 방향설정1
    digitalWrite(5, LOW);     // Motor B 방향설정2
    analogWrite(3, 255);
  }
