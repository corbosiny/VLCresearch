#ifndef VLCreceiver_h
#define VLCreceiver_h

#include "Arduino.h"

class VLCreceiver
{

  public:
  static const long long int standardDelayBetweenBitsInMicroseconds = 500000;
  static const char STARTBIT = '1';
  
  VLCreceiver(int voltageSensePin, int THRESHOLD = 450);

  String receiveString();
  char receiveCharacter();
  int receiveInteger();
  byte receiveRawByteValue();
  String receiveStringOfBits();
  byte convertStringOfBitsToByte(String stringOfBits);
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
