#include "VLCtransmitter.h"
int transmitterPin = 12;
VLCtransmitter transmitter = VLCtransmitter(transmitterPin);

void setup() 
{
  Serial.begin(9600);  
}

void loop() 
{
  if(Serial.available())
  {
    Serial.read(); //clearing out the serial buffer
    transmitter.sendStringToReciever("abcdefghijklmnopqrstuvwxyz");
  }
}



