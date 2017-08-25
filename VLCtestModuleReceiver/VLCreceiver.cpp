#include "VLCreceiver.h"

VLCreceiver::VLCreceiver(int voltageSensePin, int threshold = 450)
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
  messageReceived.remove(messageReceived.length() - 1); //removing the null character from the end
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
  String stringOfBits = receiveStringOfBits();
  return convertStringOfBitsToByte(stringOfBits);
}

String VLCreceiver::receiveStringOfBits()
{
  String stringOfBits = "";
  waitForStartBit();
  for(int bitNumber = 0; bitNumber < 8; bitNumber++)
  {
    stringOfBits += receiveBit();
    delayMicroseconds(standardDelayBetweenBitsInMicroseconds);
  }
  updateEnvironmentalNoiseReading();
  Serial.println("received byteString: " + stringOfBits);
  return stringOfBits;
}


void VLCreceiver::waitForStartBit()
{
  while(receiveBit() == '0')
  {
    ;
  }
  delayMicroseconds(standardDelayBetweenBitsInMicroseconds / 2); //puts our readings in the center of the bit transfers where it is most stable
}


char VLCreceiver::receiveBit()
{
  char bitReceived;
  if(getSensorReading() >= THRESHOLD + currentEnvironmentalNoiseReading)
  {
    bitReceived = '1';
  }
  else
  {
    bitReceived = '0';
  }
  return bitReceived;
}


byte VLCreceiver::convertStringOfBitsToByte(String stringOfBits)
{
  byte byteValue = 0;
  for(int bitIndex = 0; bitIndex < stringOfBits.length(); bitIndex++)
  {
    byteValue += pow(2, stringOfBits.length() - bitIndex - 1) * atoi(stringOfBits[bitIndex]);
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
