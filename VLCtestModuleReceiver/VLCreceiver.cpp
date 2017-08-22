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
 Serial.println("Recieving character..");
 String byteString = receiveByteString();
 Serial.print("Character recieved: ");
 Serial.println(convertByteStringToCharacter(byteString));
 return convertByteStringToCharacter(byteString);
}


String VLCreceiver::receiveByteString()
{
  String byteString = "";
  Serial.println("Recieving byte String..");
  waitForStartBit();
  for(int bitNumber = 0; bitNumber < 8; bitNumber++)
  {
    byteString += receiveBit();
  }
  updateEnvironmentalNoiseReading();
  Serial.println("recieved byte string: " + byteString);
  return byteString;
}


void VLCreceiver::waitForStartBit()
{
  while(getSensorReading() < currentEnvironmentalNoiseReading + THRESHOLD)
  {;}
  delayMicroseconds(standardDelayInMicroseconds / 2);
  delayMicroseconds(standardDelayInMicroseconds);
  Serial.println("Start bit recieved");
}


char VLCreceiver::receiveBit()
{
  char bitReceived;
  Serial.println("recieving bit..");
  if(getSensorReading() > THRESHOLD + currentEnvironmentalNoiseReading)
  {
    bitReceived = '1';
  }
  else
  {
    bitReceived = '0';
  }
  delayMicroseconds(standardDelayInMicroseconds);
  Serial.print("Bit recieved: ");
  Serial.println(bitReceived);
  return bitReceived;
}


char VLCreceiver::convertByteStringToCharacter(String byteString)
{
  int asciiValue = 0;
  for(int bitIndex = 0; bitIndex < byteString.length(); bitIndex++)
  {
    asciiValue += pow(2, byteString.length() - bitIndex - 1) * byteString[bitIndex];
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
  this->currentEnvironmentalNoiseReading = analogRead(voltageSensorPin);
}

