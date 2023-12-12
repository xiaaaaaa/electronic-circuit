//#include <analogWrite.h>
const int mose_code=15;
const int change=16;
const int btn=17;
const int q1=26,q2=25,q3=33,q4=32,q5=27;
const int Q1[12]={0,0,0,2,0,0,1,2,0,0,0,3};  //0短 1長 2換字母
const int Q2[16]={1,1,2,0,2,0,0,2,0,1,1,1,2,0,0,3};
const int Q3[12]={0,0,2,1,0,1,2,0,2,0,1,3};
const int Q4[12]={1,1,0,2,0,1,2,1,0,1,1,3};
const int Q5[19]={1,0,1,0,2,0,1,0,0,2,1,1,1,2,1,0,1,0,3};
byte ps=1, ns=1;
int level=1;


void show_short(){
  check_btn();
  Serial.println("mose code:0"); 
  Serial.println("==========");
  for(int i=0; i<100; i=i+5){     //調整i的上限，調整亮度  //調整每次遞增的數值，0~上限越快到達，閃得速度越快
    analogWrite(mose_code,i);
    delay(10); //亮度遞增減時的間隔
  }
  for(int i=100; i>-1; i=i-5){
    analogWrite(mose_code,i);
    delay(10);
  }
  delay(200);
}

void show_long(){
  check_btn();
  Serial.println("mose code:1"); 
  Serial.println("==========");
  for(int i=0; i<100; i=i+5){     //調整i的上限，調整亮度  //調整每次遞增的數值，0~上限越快到達，閃得速度越快
    analogWrite(mose_code,i);
    delay(10); //亮度遞增減時的間隔
  }
  delay(500);
  for(int i=100; i>-1; i=i-5){
    analogWrite(mose_code,i);
    delay(10);
  }
  delay(200);
}

void change_letter(){
  check_btn();
  Serial.println("mose code:2"); 
  Serial.println("==========");  
  for(int i=0; i<100; i=i+5){     //調整i的上限，調整亮度  //調整每次遞增的數值，0~上限越快到達，閃得速度越快
    analogWrite(change,i);
    delay(10); //亮度遞增減時的間隔
  }
  for(int i=100; i>-1; i=i-5){
    analogWrite(change,i);
    delay(10);
  }
  delay(500);
}

void show_level(const int mose[]){
  change_letter();
  change_letter();
  for(int i=0; mose[i]!=3; i++){
     if(mose[i]==0)  show_short();
     else if(mose[i]==1)  show_long();
     else if(mose[i]==2)  change_letter();
  }
}

void light_level(){
  if(level==1){
    analogWrite(q1,150);
    analogWrite(q2,0);
    analogWrite(q3,0);
    analogWrite(q4,0);
    analogWrite(q5,0);
  }
  else if(level==2){
    analogWrite(q1,0);
    analogWrite(q2,150);
    analogWrite(q3,0);
    analogWrite(q4,0);
    analogWrite(q5,0);
  }
  else if(level==3){
    analogWrite(q1,0);
    analogWrite(q2,0);
    analogWrite(q3,150);
    analogWrite(q4,0);
    analogWrite(q5,0);
  }
  else if(level==4){
    analogWrite(q1,0);
    analogWrite(q2,0);
    analogWrite(q3,0);
    analogWrite(q4,150);
    analogWrite(q5,0);
  }
  else if(level==5){
    analogWrite(q1,0);
    analogWrite(q2,0);
    analogWrite(q3,0);
    analogWrite(q4,0);
    analogWrite(q5,150);
  }
}

void check_btn(){
  light_level();
  ns=digitalRead(btn);
  if(ns==0&&ps==1){
    if(level==5){
      level=1;
    }
    else{
      level++;
    } 
  }
  Serial.print("level:");
  Serial.print(level);
  Serial.print(" //ps：");
  Serial.print(ps);
  Serial.print(" ns:");
  Serial.print(ns);
  Serial.println(" ");
  
  //delay(1000);
  ps=ns; 
}


void setup() {
  Serial.begin(9600);
  pinMode(mose_code,OUTPUT);
  pinMode(change,OUTPUT);
  pinMode(btn,INPUT_PULLUP);
  pinMode(q1,OUTPUT);
  pinMode(q2,OUTPUT);
  pinMode(q3,OUTPUT);
  pinMode(q4,OUTPUT);
  pinMode(q5,OUTPUT);
}

void loop(){
  if(level==1){
    
    show_level(Q1);
    
  }
  else if(level==2){
    show_level(Q2);
  }
  else if(level==3){
    show_level(Q3);
  }
  else if(level==4){
    show_level(Q4);
  }
  else if(level==5){
    show_level(Q5);
  }
}
