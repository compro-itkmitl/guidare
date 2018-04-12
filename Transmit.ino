#include <SPI.h>
#include "RF24.h"
RF24 radio(9, 10);
const uint64_t send_pipe=0xB01DFACECEL;//this device
const uint64_t recv_pipe=0xDEADBEEFF1L;//other device
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyroIC1(0x68);
MPU6050 accelgyroIC2(0x69);
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
int data[2];
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  accelgyroIC1.initialize();
  accelgyroIC2.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyroIC1.testConnection());
  Serial.println("Start");
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setRetries(15,15);
  radio.openWritingPipe(recv_pipe);
  radio.openReadingPipe(1,send_pipe);
  radio.startListening();
}
#define CODE_NONE 0
unsigned long message_code=CODE_NONE;
void loop()
{
  accelgyroIC1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
  data[0] = map(ax1, -17000, 17000, 300, 400 ); //Send X axis data
  data[1] = map(ay1, -17000, 17000, 100, 200);  //Send Y axis data
//Serial.print("X: ");
  //Serial.println(data[0]);
  //Serial.print("y: ");
  //Serial.println(data[1]);
  if(data[0] < 340){
        //forward            
        Serial.println("forward");
        message_code = forward;
      }
  if(data[0] > 360){
        //backward              
        Serial.println("backward");
        message_code = backward;
      }
       
      if(data[1] < 145){
        //left
        Serial.println("left");
        message_code = left;
      }
  
      if(data[1] > 155){
        //right
        Serial.println("right");
        message_code = right;
      }
      if(data[0] > 340 && data[0] < 360 && data[1] > 145 && data[1] < 155){
        //stop car
        Serial.println("stop");
        message_code = stopi;
      }
  if(message_code!=CODE_NONE)
  {
    radio.stopListening();
    if(!radio.write(&message_code, sizeof(unsigned long)))
    {
      Serial.println("Failed");
    }

    radio.startListening();

    unsigned long started_waiting_at=micros();
    boolean timeout=false;

    while(!radio.available())
    {
      if(micros()-started_waiting_at>200000)
      {
        timeout=true;
        break;
      }      
    }
    if(timeout==true)
    {
      Serial.println("Timeout");
    }
    else
    {
      unsigned long in_data;
      radio.read(&in_data, sizeof(unsigned long));
      Serial.println("In Data: "+String(in_data));
    }
    delay(500);
  }
 
}

