#ifndef VLCtransmitter_h
#define VLCtransmitter_h

#include "Arduino.h"

class VLCtransmitter
{
  
  public:
  static const long long int standardDelayBetweenBitsInMicroseconds = 500000;
  static const char STARTBIT = '1';
  static const char ENDBIT = '0'; 
  
  VLCtransmitter(int signalPin);
  
  void sendStringToReceiver(String message);
  void sendCharacterToReceiver(char character);
  void sendIntegerToReceiver(int integerValue);
  void sendByteToReceiver(byte byteValue);
  String convertByteToStringOfBits(byte byteValue);
  void sendStringOfBits(String byteString);
  void sendBit(char bitToSend);
  
  private:
  int transistorSignalPin;
  
};


#endif
