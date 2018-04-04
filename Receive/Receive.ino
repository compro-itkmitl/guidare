#include <SPI.h>
#include "RF24.h"
RF24 radio(9, 10);//commu NRF24L01
const uint64_t send_pipe=0xB01DFACECEL;
const uint64_t recv_pipe=0xDEADBEEFF1L;
#define CODE_NONE 0

void setup()
{
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
 
  }
}

