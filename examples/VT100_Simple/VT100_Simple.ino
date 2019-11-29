#include <VT100.h>



void setup()
{
  Serial.begin(9600);
  VT100.begin(Serial);

  Serial.write("I am a simple counter: ");
}

void loop()
{
  VT100.setCursor(1, 24);
  Serial.print((float)millis()/1000.0);
  VT100.clearLineAfter();
}
