#ifndef VLCtransmitter_h
#define VLCtransmitter_h

#include "Arduino.h"

class VLCtransmitter
{
  
  public:
  static const long long int standardDelayInMicroseconds = 500000;
  static const char STARTBIT = '1';
  static const char ENDBIT = '0';
  
  VLCtransmitter(int signalPin);
  void sendStringToReciever(String message);
  void sendCharacterToReciever(char character);
  String convertCharacterToByteString(char character);
  void sendByteString(String byteString);
  void sendBit(char bitToSend);
  
  private:
  int transistorSignalPin;
  
};


#endif
