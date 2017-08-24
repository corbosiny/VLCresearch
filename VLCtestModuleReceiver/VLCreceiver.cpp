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
  char lastCharacterReceived = '_'; 
  while(lastCharacterReceived != '\0')
  {
    lastCharacterReceived = receiveCharacter();
    messageReceived += lastCharacterReceived;
  }
  messageReceived.remove(messageReceived.length()); //removing the null character from the end
  return messageReceived;
}

char VLCreceiver::receiveCharacter()
{
 char charReceived = (char)receiveRawByteValue();
 return charReceived;
}


int VLCreceiver::receiveInteger()
{
  int numberReceived = (int)receiveRawByteValue();
  return numberReceived;
}

byte VLCreceiver::receiveRawByteValue()
{
  String byteString = receiveStringOfBits();
  return convertStringOfBitsToByte(byteString);
}

String VLCreceiver::receiveStringOfBits()
{
  String stringOfBits = "";
  waitForStartBit();
  for(int bitNumber = 0; bitNumber < 8; bitNumber++)
  {
    stringOfBits += receiveBit();
  }
  updateEnvironmentalNoiseReading();
  Serial.println("received byteString: " + stringOfBits);
  return stringOfBits;
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


byte VLCreceiver::convertStringOfBitsToByte(String stringOfBits)
{
  byte byteValue = 0;
  for(int bitIndex = 0; bitIndex < stringOfBits.length(); bitIndex++)
  {
    byteValue += pow(2, stringOfBits.length() - bitIndex - 1) * ((int)stringOfBits[bitIndex] - 48);
  }
  return byteValue;
}


int VLCreceiver::getSensorReading()
{
  return analogRead(voltageSensorPin);
}


void VLCreceiver::updateEnvironmentalNoiseReading()
{
  this->currentEnvironmentalNoiseReading = 0; //temporarly turned off
}
