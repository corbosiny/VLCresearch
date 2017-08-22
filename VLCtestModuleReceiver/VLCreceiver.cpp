#include "VLCreceiver.h"

VLCreceiver::VLCreceiver(int voltageSensePin, int threshold)
{
  this->voltageSensorPin = voltageSensePin; 
  this->THRESHOLD = threshold;
  this->currentEnvironmentalNoiseReading = analogRead(voltageSensePin);
}


String VLCreceiver::receiveString()
{
  String messageReceived = "";
  while(true)
  {
    char characterReceived = receiveCharacter();
    if(characterReceived == 0) //null character signals end of string
    {
      return messageReceived;
    }
    else
    {
      messageReceived += characterReceived;
    }
  }
}


char VLCreceiver::receiveCharacter()
{
 String byteString = receiveByteString();
 return convertByteStringToCharacter(byteString);
}


String VLCreceiver::receiveByteString()
{
  String byteString = "";
  waitForStartBit();
  for(int bitNumber = 0; bitNumber < 8; bitNumber++)
  {
    byteString += receiveBit();
  }
  updateEnvironmentalNoiseReading();
  Serial.println("received byteString: " + byteString);
  return byteString;
}


void VLCreceiver::waitForStartBit()
{
  while(receiveBit() == '0')
  {;}
  delayMicroseconds(standardDelayInMicroseconds / 2); //puts our readings in the center of the bit transfers where it is most stable
}


char VLCreceiver::receiveBit()
{
  char bitReceived;
  if(getSensorReading() > THRESHOLD + currentEnvironmentalNoiseReading)
  {
    bitReceived = '1';
  }
  else
  {
    bitReceived = '0';
  }
  delayMicroseconds(standardDelayInMicroseconds);
  return bitReceived;
}


char VLCreceiver::convertByteStringToCharacter(String byteString)
{
  int asciiValue = 0;
  for(int bitIndex = 0; bitIndex < byteString.length(); bitIndex++)
  {
    asciiValue += pow(2, byteString.length() - bitIndex - 1) * ((int)byteString[bitIndex] - 48);
  }
  char convertedCharacter = asciiValue;
  return convertedCharacter;
}


int VLCreceiver::getSensorReading()
{
  return analogRead(voltageSensorPin);
}


void VLCreceiver::updateEnvironmentalNoiseReading()
{
  this->currentEnvironmentalNoiseReading = 0; //temporarly turned off
}
