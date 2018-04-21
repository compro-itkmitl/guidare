#include <SPI.h>
#include "RF24.h"
RF24 radio(9, 10); // Establish a new RF24 object
const uint64_t send_pipe=0xB01DFACECEL;//This will be this device
const uint64_t recv_pipe=0xDEADBEEFF1L;//This will be the other device
//implementation
// is used in I2Cdev.h
#include "Wire.h"
 
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h
//files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
 
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;
MPU6050 accelgyroIC1(0x68);
MPU6050 accelgyroIC2(0x69);
 
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
 
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
int data[2];
void setup()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  // initialize device
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  //accelgyro.initialize();
  accelgyroIC1.initialize();
  accelgyroIC2.initialize();
  
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyroIC1.testConnection());// "MPU6050 #1 connection
  Serial.println("Start");
  radio.begin();// Basically turn on communications with the device
  radio.setPALevel(RF24_PA_LOW);//RF24_PA_MAX is max power
  radio.setRetries(15,15);//This will improve reliability
  radio.openWritingPipe(recv_pipe);//Set up the two way communications with the named device
  radio.openReadingPipe(1,send_pipe);
  radio.startListening();// Start listening for data which gives the device a kick
}
//These are the four codes that we will work with, the final three being those that are transmitted
#define CODE_NONE 0
#define forward 1
#define backward 2
#define left 3
#define right 4
#define stopi 5
unsigned long message_code=CODE_NONE;//This is where the code to be sent will reside
void loop()
{
  // read raw accel/gyro measurements from device
  accelgyroIC1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
  data[0] = map(ax1, -17000, 17000, 300, 400 ); //Send X axis data
  data[1] = map(ay1, -17000, 17000, 100, 200);  //Send Y axis data
  //Serial.print("X: ");
  //Serial.println(data[0]);
  //Serial.print("y: ");
  //Serial.println(data[1]);
  if(data[0] < 330){
        //forward            
        Serial.println("forward");
        message_code = forward;
      }
  if(data[0] > 370){
        //backward              
        Serial.println("backward");
        message_code = backward;
      }
       
      if(data[1] < 130){
        //left
        Serial.println("left");
        message_code = left;
      }
  
      if(data[1] > 170){
        //right
        Serial.println("right");
        message_code = right;
      }
      if(data[0] > 330 && data[0] < 370 && data[1] > 130 && data[1] < 170){
        //stop car
        Serial.println("stop");
        message_code = stopi;
      }
  if(message_code!=CODE_NONE)//If something is to be done then send the code
  {
    radio.stopListening();//We are sending not listening for now
    if(!radio.write(&message_code, sizeof(unsigned long)))// Send the message_code and check to see if it comes back false
    {
      Serial.println("Failed");
    }
 
    radio.startListening();//Go back to listening and wait for the ack signal.
 
    unsigned long started_waiting_at=micros();//This notes the time 
    boolean timeout=false;//Assume for the moment that there is no timeout
 
    while(!radio.available())//Keep looping while no ack has come in
    {
      if(micros()-started_waiting_at>200000)//If the loop has been going for more than 1/5th of a second then give up
      {
        timeout=true; //Note that it has failed
        break;
      }      
    }
    if(timeout==true)//If the previous looped marked as failure then 
    {
      Serial.println("Timeout");
    }
    else// If it didn't fail to ack then read in and printout the results.
    {
      unsigned long in_data;
      radio.read(&in_data, sizeof(unsigned long));
      Serial.println("In Data: "+String(in_data));
    }
    delay(450);
  }
 
}
