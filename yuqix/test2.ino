#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

int led_1=16; // 正確LED
int led_2=15; //錯誤LED
String anser;
int i=1;
void setup(){
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT31"); //藍牙顯示名稱，可自行更改，需避免與他人重複命名
  pinMode(16,OUTPUT);
  pinMode(15,OUTPUT);
}

void loop(){
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.println(SerialBT.readString());
  }

while(i!=2){
  if (SerialBT.available()){
    anser = SerialBT.readString();

  
   if(anser == "sus"){
      //正確，開啟LED
      digitalWrite(16, HIGH);
      Serial.println("正確，開啟LED1");
      delay(1000);
      digitalWrite(15, LOW);
      anser = SerialBT.readString();
      i++;
    }
   else{
      digitalWrite(led_2, HIGH);
      Serial.println("錯誤，開啟LED2");
      delay(1000);
      digitalWrite(led_2, LOW);
      anser = SerialBT.readString();

      }
    }
}
while(i!=3){  
  if (SerialBT.available()) {
    anser = SerialBT.readString();
    if(anser == "meiji"){
      //正確，開啟LED
      digitalWrite(led_1, HIGH);
      Serial.println("正確，開啟LED1");
      delay(1000);
      digitalWrite(led_1, LOW);
      i++;
    }
    else{
      digitalWrite(led_2, HIGH);
      Serial.println("錯誤，開啟LED2");
      delay(1000);
      digitalWrite(led_2, LOW);
    }
  }
}
while(i!=4){
  if(SerialBT.available()){
    anser = SerialBT.readString();
    if(anser == "ikea") {
      //正確，開啟LED
      digitalWrite(led_1, HIGH);
      Serial.println("正確，開啟LED1");
      delay(1000);
      digitalWrite(led_1, LOW);
      i++;
    }
    else{
      digitalWrite(led_2, HIGH);
      Serial.println("錯誤，開啟LED2");
      delay(1000);
      digitalWrite(led_2, LOW);
    }
  }
}
while(i!=5){
  if(SerialBT.available()) {
    anser = SerialBT.readString();
    if(anser == "gay"){
      //正確，開啟LED
      digitalWrite(led_1, HIGH);
      Serial.println("正確，開啟LED1");
      delay(1000);
      digitalWrite(led_1, LOW);
      i++;
    }
    else{
      digitalWrite(led_2, HIGH);
      Serial.println("錯誤，開啟LED2");
      delay(1000);
      digitalWrite(led_2, LOW);
    }
  }
}
while(i!=6){
  if(SerialBT.available()) {
    anser = SerialBT.readString();
    if (anser == "cloc") {
      //正確，開啟LED
      digitalWrite(led_1, HIGH);
      Serial.println("正確，開啟LED1");
      delay(1000);
      digitalWrite(led_1, LOW);
      i++;
    }
    else{
      digitalWrite(led_2, HIGH);
      Serial.println("錯誤，開啟LED2");
      delay(1000);
      digitalWrite(led_2, LOW);
    }
  }
}

  delay(50);
}
