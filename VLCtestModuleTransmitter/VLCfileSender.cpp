#include "VLCfileSender.h"

VLCfileSender::VLCfileSender(int voltageSensePin, int baudRate = 9600)
{
  this->baudRate = baudRate;
  this->physicalTransmitter = new VLCtransmitter(voltageSensePin);
  initializeSerialPort();
}

void VLCfileSender::initializeSerialPort()
{
  if(!Serial) 
  {
    Serial.begin(this->baudRate);
  }
}

void VLCfileSender::transmitFile()
{
  String fileName = getStringOfBytesFromUser();
  String fileData = getStringOfBytesFromUser();
  this->physicalTransmitter.sendStringToReceiver(fileName);
  this->physicalTransmitter.sendStringToReceiver(fileData);
}

String VLCfileSender::getStringOfBytesFromUser()
{
  char lastByteReceived = '_'; //any arbitrary value, the compiler forces us to initialzie it to something
  String stringOfBytes = "";
  while(lastByteReceived != '\0')
  {
    waitForByte();
    lastByteReceived = Serial.read(); //we cast the bytes as character just so we can store them all sequentially in a string
    stringOfBytes += lastByteReceived; 
  }
  return stringOfBytes;
}

void VLCfileSender::waitForByte()
{
  while(!Serial.available())
  {
   ;
  }
}

