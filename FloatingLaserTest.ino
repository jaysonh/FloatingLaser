#include <IRremote.h> 
#include "MPU9250.h"

MPU9250 mpu; // You can also use MPU9255 as is
           
const int irRecvPin = 10;
const int laserPin  = A7; 
bool laserOn = false;

long lastRecv = 0;
long recvThresh = 250; // ms


void setup() {
  pinMode( laserPin, OUTPUT);

  IrReceiver.begin(irRecvPin); // Initializes the IR receiver object
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  mpu.setup(0x68);  // change to your own address

}

void loop() 
{ 


  Serial.println(analogRead(A10));
  int result = IrReceiver.decode();
  if (result ) 
  {
    if(millis() - lastRecv > recvThresh)
    {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.resume(); // Important, enables to receive the next IR signal

      if( IrReceiver.decodedIRData.decodedRawData != 0)
      {
          laserOn = !laserOn;
      
          if(laserOn) 
            digitalWrite(laserPin, HIGH);
          else
            digitalWrite(laserPin, LOW);
      } 
      lastRecv = millis();
    }    
  }        
}
 
