#ifndef VLCfileReceiver_h
#define VLCfileReceiver_h

#include "Arduino.h"
#include "VLCreceiver.h"


class VLCfileReceiver
{

  public:
  VLCfileReceiver(int voltageSensorPin, int baudRate = 9600, int threshold = 450);
  void receiveAndPassOffFile();
  

  private:
  VLCreceiver physicalReceiver = NULL;
  int baudRate;

  void initializeSerialPort();
  void passFileOffToUser(String fileName, String fileData);
  
};

#endif
