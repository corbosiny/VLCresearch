#ifndef VLCfileReceiver_h
#define VLCfileReceiver_h

#include "Arduino.h"
#include "VLCreceiver.h"


class VLCfileReceiver
{

  public:
  VLCfileReceiver(int voltageSensorPin, int baudRate = 9600);
  void receiveFile();
  

  private:
  VLCreceiver physicalReceiver = null;
  int buadRate;

  void initializeSerialPort();
  void passFileOffToUser(String fileName, String fileData);
  
};

#endif
