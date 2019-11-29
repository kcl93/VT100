#include <VT100.h>


char buffer[8];

float Counter1;
uint8_t Counter2;
int16_t Counter3;


void setup()
{
  Serial.begin(9600);
  VT100.begin(Serial);

  VT100.setBackgroundColor(VT_RED);
  VT100.setTextColor(VT_YELLOW);

  Serial.println("Counter1: ");
  Serial.println();
  Serial.println("Counter2:       Counter3: ");
  
  VT100.cursorSave();
}

void loop()
{
  VT100.setCursor(1, 10);
  VT100.formatText(VT_BRIGHT);
  Serial.print((float)millis()/1000.0);
  VT100.clearLineAfter();
  
  VT100.setCursor(3, 10);
  sprintf(buffer, "%3u", millis()/10);
  VT100.formatText(VT_UNDERSCORE);
  Serial.print(buffer);
  
  VT100.cursorRestore();
  VT100.formatText(VT_DIM);
  Serial.print((int16_t)millis()/10);
  VT100.clearLineAfter();
}
