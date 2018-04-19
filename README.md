# Guidare (น้องมะลิ)

##Introduction(มีการปรับเปลี่ยนสเกลงานเเละเนื้อหาโปรเจค)
	โปรเจค Guidare คือโปรเจคที่ได้สร้างรถบังคับเเละอุปกรณ์การบังคับรถโดยใช้ MPU6050  เเละ NRF24L01 Module ซึ่งการบังคับรถของโปรเจค Guidare
นั้นมีความเเตกต่างจากการบังคับรถปกติมากนั้นเพราะโปรเจคนี้ใช้การบังคับรถโดยใช้เซนเซอร์ติดถุงมือเเล้วก็ควบคุมรถโดยใช้มือควบคุมทิศทางของรถบังคับเเละโปรเจค Guidare นั้นยังสามารถ
นำไปประยุคต์ใช้ได้อีกหลายอย่าง

## อุปกรณ์ที่ใช้
1. arduino uno 
2. arduino nano
3. MPU6050 2 ตัว
4. Gear moter with Trie 2 ตัว
5. 9110S DC STEPPER MOTOR DRIVER H-BRIDGE
6. NRF24L01 Module

## การต่อบอร์ด arduino uno 

| nrf24l01        | arduino uno   |
| --------------- |:-------------:|       
| CE 	          |  9            |
| CSN             | 10            |
| MOSI            | 11            |
| MISO            | 12            |
| SCK             | 13            |
| VCC             | 3V3           |
| GND             | GND           |

                
|  MOTOR DRIVER   |  arduino uno  |
| --------------- |:-------------:|
|    A-A          |  3            |
|    A-B          |  4            |
|    B-A          |  6            |
|    B-B          |  7            |
|    vcc          |  5V           |
|    B-B          |  GND          |



## การต่อบอร์ด arduino nano

| MPU6050         | arduino nano  |
| --------------- |:-------------:|
| VCC             | 5V            |
| GND             | GND           |
| SCL	          | A5            |
| SDA             | A4            |
| INT             | D2            |

| nrf24l01        | arduino nano  |
| --------------- |:-------------:|         	 
| VCC 	          | 5V            |
| GND             | GND           |
| CE              | D9            |
| CNS             | D10           |
| SCK             | D13           |
| MOSI            | D11           |
| MISO            | D12           |


## การติดตั้ง

**Requirements**
* NRF24L01 Library http://www.allarduino.com/download/nRF24L01p.rar
* MPU6050 Library https://maker.pro/files/MPU6050.zip
* I2Cdev Library https://maker.pro/files/I2Cdev.zip

## Coding
 ตัวโปรแกรมจะแบ่งเป็น 2 ส่วนคือ Transmit กับ Rececive

### Rececive
	ส่วนของ Rececive คือส่วนของรถบังคับที่จะเป็นตัวรับข้อมูลโดยใช้ NRF24L01 ที่ส่งจาก arduino nano ที่อยู่ที่ถุงมือบังคับรถ
เเละเเปลงข้อมูลเพื่อควบคุมรถด้วย STEPPER MOTOR DRIVER ที่อยู่บนบอร์ด arduino uno



### Transmit




```

## จัดทำโดย
* 60070057 : พชร ศรียอดเวียง

---

Faculty of Information Technology

King Mongkut's Institute of Technology Ladkrabang