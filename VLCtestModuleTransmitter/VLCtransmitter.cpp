#include "VLCtransmitter.h"

VLCtransmitter::VLCtransmitter(int signalPin)
{
  this->transistorSignalPin = signalPin;
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
}


void VLCtransmitter::sendStringToReciever(String message)
{ 
  Serial.println("Message Length: " + String(message.length()));
  for(int messageIndex = 0; messageIndex < message.length() + 1; messageIndex++) //.length doesnt count the null character, so we add one to make sure we include it
  {
    char currentCharacter = message[messageIndex];
    Serial.print("Sending character: ");
    Serial.println(currentCharacter);
    sendCharacterToReciever(currentCharacter);   
    Serial.println("Charcater sent!");
  }  
}

void VLCtransmitter::sendCharacterToReciever(char character)
{
  String characterAsByteString = convertCharacterToByteString(character);
  Serial.println("Character as byte string: " + characterAsByteString);
  sendByteString(characterAsByteString); 
}

String VLCtransmitter::convertCharacterToByteString(char character)
{
  int asciiValue = character;
  int currentBitIndex = 7;
  String byteString = "00000000";
  while(asciiValue > 0)
  {
    if(asciiValue % 2 == 0)
    {
      byteString[currentBitIndex] = '0'; 
    }
    else
    {
      byteString[currentBitIndex] = '1';
    }
    
    asciiValue /= 2;
    currentBitIndex--;
  }
  return byteString;
}

void VLCtransmitter::sendByteString(String byteString)
{
  sendBit(STARTBIT);
  for(int bitIndex = 0; bitIndex < byteString.length(); bitIndex++)
  {
    char bitToSend = byteString[bitIndex];
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

