// Use Seeeduino XIAO board
// Requires IRremote library and MPU9250 library installed in libraries manager
#include <IRremote.h> 
const int irRecvPin = 10;
const int laserOutputPin = A7; 

const int laserSensorPin = A5;
const int laserDetectPin = A6;

const int irOutputPin = A4;

bool laserOn = false;

long lastRecv = 0;
long recvThresh = 250; // ms

void setup() {
  pinMode( laserOutputPin, OUTPUT);

  IrReceiver.begin(irRecvPin); // Initializes the IR receiver object
  Serial.begin(9600);
 pinMode( laserSensorPin, OUTPUT);
 pinMode( irOutputPin, OUTPUT);
 digitalWrite(laserSensorPin, HIGH);
 digitalWrite(irOutputPin, HIGH);
  
}

void loop() 
{ 
  int v = analogRead( laserDetectPin );
  Serial.println(v);
  

  //Serial.println(analogRead(A10));
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
            digitalWrite(laserOutputPin, HIGH);
          else
            digitalWrite(laserOutputPin, LOW);
      } 
      lastRecv = millis();
    }    
  } 

         
  delay(50);
}


 
