//#include "pitches.h"
const int trigPin = 9;
const int echoPin = 10;
const int p1 = 8;
const int potPin = A0;
const int b1 = 6;
const int b2 = 5;
const int b3 = 4;
const int ledPin = 3;


//int scale[]={ NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1,NOTE_DS1 , NOTE_E1 ,NOTE_F1 ,NOTE_FS1 , NOTE_G1, NOTE_GS1, NOTE_A1 , NOTE_AS1 , NOTE_B1 , NOTE_C2 , NOTE_CS2 , NOTE_D2 , NOTE_DS2 , NOTE_E2 , NOTE_F2 ,
//NOTE_FS2 , NOTE_G2 , NOTE_GS2 ,  NOTE_A2 , NOTE_AS2 , NOTE_B2 , NOTE_C3 , NOTE_CS3 ,NOTE_D3 ,NOTE_DS3 ,NOTE_E3 ,NOTE_F3 ,NOTE_FS3 ,NOTE_G3 ,NOTE_GS3 ,NOTE_A3 ,NOTE_AS3 , NOTE_B3 ,NOTE_C4 ,NOTE_CS4 ,NOTE_D4 ,NOTE_DS4 ,NOTE_E4 ,
//NOTE_F4 ,NOTE_FS4 ,NOTE_G4 ,NOTE_GS4 ,NOTE_A4 ,NOTE_AS4 ,NOTE_B4 ,NOTE_C5 , NOTE_CS5 , NOTE_D5 , NOTE_DS5 , NOTE_E5 , NOTE_F5 , NOTE_FS5 , NOTE_G5 , NOTE_GS5 , NOTE_A5 , NOTE_AS5 , NOTE_B5 , NOTE_C6 , NOTE_CS6 , NOTE_D6 ,
//NOTE_DS6 ,NOTE_E6 ,NOTE_F6 ,NOTE_FS6 ,NOTE_G6 ,NOTE_GS6 ,NOTE_A6 ,NOTE_AS6 ,NOTE_B6 ,NOTE_C7 };

//int CMAJOR[]={NOTE_C3 ,NOTE_D3 ,NOTE_E3 ,
//NOTE_F3 ,NOTE_G3  ,NOTE_A3 ,NOTE_B3,NOTE_C4 ,NOTE_D4 ,NOTE_E4 ,
//NOTE_F4 ,NOTE_G4  ,NOTE_A4 ,NOTE_B4 ,NOTE_C5};
//make different scales

int vout;
float distance;
float duration;
int index;
int note;
int maxDistance = 60;
int frequency;
int average;
int b1State= HIGH;
int b2State=HIGH;
int b3State = HIGH;
bool isPressedAgain=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT );
  pinMode(p1,OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9000);
}

void tom(int pin,int frequency){
     for(int i = 0; i < 6; i++){
        tone(pin, frequency);
        delay(20);
        noTone(pin);
        frequency -= 80; 
      }
}

void kick(int pin){
  for(int i=0; i<4 ;i++){
    tone(pin,50);
    delay(10);
    noTone(pin);
    frequency-=10;
  }
}

void noise(int pin){
  for(int i = 0; i < 6; i++){
        tone(pin, random(0,1000));
        delay(random(0,3));
      }
}

void record(){
  for(int i=0; i<8;i++){
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500 );  
  }
}

void readAllButtonStates(){
  b1State=digitalRead(b1);  
  b2State=digitalRead(b2);
  b3State=digitalRead(b3);
}
int readKnob(int pin){
  vout=analogRead(pin);
  return map(vout, 0, 1023, 750, 50);
}

int prevState1;
int prevState2;
int prevState3;

void loop(){    

  //record();

  readAllButtonStates();

  frequency=readKnob(potPin);
  
  if(b1State == LOW && prevState1==HIGH){
    tom(p1, frequency);
  }
  prevState1 = b1State;

  if(b2State == LOW && prevState2==HIGH){
    tom(p1, frequency+100);
  }
  prevState2 = b2State;

  if(b3State == LOW && prevState3 == HIGH){
    kick(p1);
  }
  prevState3 = b3State;

   delay(10);
  
}

//hee hee
//  while(b1State==HIGH){ 
//    b1State = digitalRead(b1);
//    if(b1State==LOW){
//      vout = analogRead(potPin);
//      frequency = map(vout, 0, 1023, 750, 50);
//      tom(p1,frequency);
//      //break;
//    }
//  }
// 
//  noTone(p1);
//  b1State = digitalRead(b1);
//  delay(50);
