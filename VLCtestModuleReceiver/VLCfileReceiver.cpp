#include "VLCfileReceiver.h"

VLCfileReceiver::VLCfileReceiver(int voltageSensorPin, int baudRate = 9600, int threshold = 450)
{
 this->physicalReceiver = new VLCreceiver(voltageSensorPin, threshold);
 this->baudRate = baudRate;
 initializeSerialPort(); 
}


void VLCfileReceiver::initializeSerialPort()
{
  if(!Serial)
  {
    Serial.begin(this->baudRate);
  }
  
}


void VLCfileReceiver::receiveAndPassOffFile()
{
  String fileName = this->physicalReceiver.receiveString();
  String fileData = this->physicalReceiver.receiveString();
  passFileOffToUser(fileName, fileData); 
}

void VLCfileReceiver::passFileOffToUser(String fileName, String fileData)
{
  Serial.print(fileName);
  Serial.write(0);
  Serial.print(fileData);
  Serial.write(0);
}

