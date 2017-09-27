//#include <EEPROM.h> //' A{
#include <SPI.h>
#include <GD2.h>

void setup()
{
  Serial.begin(9600); // JCB
  GD.begin();
}

void loop()
{
  GD.ClearColorRGB(0x103000);
  GD.Clear();
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello world");
  GD.swap();
} //' }A
