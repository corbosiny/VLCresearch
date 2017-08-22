#ifndef VLCreceiver_h
#define VLCreceiver_h

#include "Arduino.h"

class VLCreceiver
{

  public:
  static const int standardDelayInMicroseconds = 30000;
  static const char STARTBIT = '1';
  VLCreceiver(int voltageSensePin, int THRESHOLD);

  String receiveString();
  char receiveCharacter();
  String receiveByteString();
  char convertByteStringToCharacter(String byteString);
  void waitForStartBit();
  char receiveBit();

  void updateEnvironmentalNoiseReading();
  
  private:
  int voltageSensorPin;
  int THRESHOLD;
  int currentEnvironmentalNoiseReading;
     
  int getSensorReading();
  
};


#endif
