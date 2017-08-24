#include "VLCtransmitter.h"

VLCtransmitter::VLCtransmitter(int signalPin)
{
  this->transistorSignalPin = signalPin;
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
}


void VLCtransmitter::sendStringToReceiver(String message)
{ 
  for(int messageIndex = 0; messageIndex < message.length() + 1; messageIndex++) //.length doesnt count the null character, so we add one to make sure we include it
  {
    char currentCharacter = message[messageIndex];
    sendCharacterToReceiver(currentCharacter);   
  }  
}

void VLCtransmitter::sendCharacterToReceiver(char character)
{
  sendByteToReceiver((byte)character);
}

void VLCtransmitter::sendIntegerToReceiver(int integerValue)
{
  sendByteToReceiver((byte)integerValue);
}

void VLCtransmitter::sendByteToReceiver(byte byteValue)
{
  String stringOfBits = convertByteToStringOfBits(byteValue);
  sendStringOfBits(stringOfBits);
}

String VLCtransmitter::convertByteToStringOfBits(byte byteValue)
{
  int currentBitIndex = 7;
  String stringOfBits = "00000000";
  while(byteValue > 0)
  {
    if(byteValue % 2 == 0)
    {
      stringOfBits[currentBitIndex] = '0'; 
    }
    else
    {
      stringOfBits[currentBitIndex] = '1';
    }
    
    byteValue /= 2;
    currentBitIndex--;
  }
  return stringOfBits;
}

void VLCtransmitter::sendStringOfBits(String stringOfBits)
{
  sendBit(STARTBIT);
  for(int bitIndex = 0; bitIndex < stringOfBits.length(); bitIndex++)
  {
    char bitToSend = stringOfBits[bitIndex];
    sendBit(bitToSend);
  }
  sendBit(ENDBIT);
}

void VLCtransmitter::sendBit(char bitToSend)
{
  if(bitToSend == '1') 
  {
    digitalWrite(transistorSignalPin, HIGH);
  }
  else
  {
    digitalWrite(transistorSignalPin, LOW);
  }
  delayMicroseconds(standardDelayInMicroseconds);

}

