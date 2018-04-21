#include <SPI.h>
#include "RF24.h"
RF24 radio(9, 10);//commu NRF24L01
const uint64_t send_pipe=0xB01DFACECEL;
const uint64_t recv_pipe=0xDEADBEEFF1L;
#define CODE_NONE 0
#define forward 1
#define backward 2
#define left 3
#define right 4
#define stopi 5
#define motor_aa 3
#define motor_ab 4
#define motor_ba 6
#define motor_bb 7

void setup()
{
   pinMode(motor_aa,OUTPUT);
   pinMode(motor_ab,OUTPUT);
   pinMode(motor_ba,OUTPUT);
   pinMode(motor_bb,OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready for commands");
  radio.begin();
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_LOW); //range increase 
  radio.openWritingPipe(send_pipe);
  radio.openReadingPipe(1,recv_pipe);
  radio.startListening();

}

void loop()
{
  unsigned long motor_code=CODE_NONE;
  if( radio.available())
  {
    while(radio.available())
    {
      radio.read(&motor_code, sizeof(unsigned long));
    }
    radio.stopListening();
    radio.write(&motor_code, sizeof(unsigned long));
    radio.startListening();
    Serial.println(motor_code);
    if(motor_code==backward){
      Serial.println("backward");
      digitalWrite(motor_aa,LOW);
      digitalWrite(motor_ab,HIGH);
      digitalWrite(motor_ba,LOW);
      digitalWrite(motor_bb,HIGH);
    }else if(motor_code==forward){
      Serial.println("forward");
      digitalWrite(motor_aa,HIGH);
      digitalWrite(motor_ab,LOW);
      digitalWrite(motor_ba,HIGH);
      digitalWrite(motor_bb,LOW);
    }else if(motor_code==right){
      Serial.println("right");
      digitalWrite(motor_aa,HIGH);
      digitalWrite(motor_ab,LOW);
      digitalWrite(motor_ba,LOW);
      digitalWrite(motor_bb,HIGH);
    }else if(motor_code==left){
      Serial.println("left");
      digitalWrite(motor_aa,LOW);
      digitalWrite(motor_ab,HIGH);
      digitalWrite(motor_ba,HIGH);
      digitalWrite(motor_bb,LOW); 
    }else if(motor_code==stopi){
      Serial.println("stop");
      digitalWrite(motor_aa,HIGH);
      digitalWrite(motor_ab,HIGH);
      digitalWrite(motor_ba,HIGH);
      digitalWrite(motor_bb,HIGH);
    }else{
      Serial.println("error..");
    }
  }else{
      Serial.println("radio error...");
    }
   delay(500);
}

