#include VLCfileReceiver

VLCfileReceiver::VLCfileReceiver(int voltageSensorPin, int baudRate = 9600)
{
 this->voltageSensorPin = voltageSensorPin;
 this->buadRate = buadRate;
 initializeSerialPort(); 
}


VLCfileReceiver::initializeSerialPort()
{
  if(!Serial)
  {
    Serial.begin(this->baudRate);
  }
  
}


VLCfileReceiver::receiveFile()
{
  String fileName = this->physicalReceiver.receiveString();
  String fileData = this->physicalReceiver.receiveString();
  passFileOffToUser(fileName, fileData); 
}

VLCfileReceiver::passFileOffToUser(String fileName, String fileData)
{
  Serial.write(fileName);
  Serial.write(0);
  Serial.write(fileData);
  Serial.write(0);
}

