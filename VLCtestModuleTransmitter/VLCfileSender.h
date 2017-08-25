#ifndef VLCfileSender_h
#define VLCfileSender_h

#include "Arduino.h"
#include "VLCtransmitter.h"

class VLCfileSender
{

  public:
    VLCfileSender(int voltageSensorPin, int buadRate = 9600);
    void transmitFile();
    
  private:
    VLCtransmitter physicalTransmitter = NULL;
    int baudRate = 9600;

    void initializeSerialPort();
    String getStringOfBytesFromUser();
    void waitForByte();
};

#endif
