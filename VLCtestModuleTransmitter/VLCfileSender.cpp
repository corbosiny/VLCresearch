#include "VLCfileSender.h"

VLCfileSender::VLCfileSender(int voltageSensePin, int baudRate = 9600)
{
  initializeSerialPort(baudRate);
  this->baudRate = baudRate;
  this->transmitter = new VLCtransmitter(voltageSensePin);
}

void VLCfileSender::initializeSerialPort(int buadRate)
{
  if(!Serial) 
  {
    Serial.begin(baudRate);
  }
}

void VLCfileSender::transmitFile()
{
  String fileName = getStringOfBytesFromUser();
  String fileData = getStringOfBytesFromUser();
  this->transmitter.sendStringToReceiver(fileName);
  this->transmitter.sendStringToReceiver(fileData);
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

