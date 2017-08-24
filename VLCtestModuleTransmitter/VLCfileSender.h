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
    VLCtransmitter transmitter = NULL;
    int baudRate = 9600;

    void initializeSerialPort(int buadRate);
    String getStringOfBytesFromUser();
    static void waitForByte();
};

#endif
