#include "VLCreceiver.h"

int voltageSensor = A0;
int THRESHOLD = 450;
VLCreceiver receiver = VLCreceiver(A0, THRESHOLD);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.println("Recieving message..");
  Serial.println(receiver.receiveString());
  Serial.println("message recieved!\n");
}
