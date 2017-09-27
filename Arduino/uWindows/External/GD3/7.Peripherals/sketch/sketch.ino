#include <SPI.h>
#include <GD2.h>

void setup()
{
  GD.begin();
  GD.cmd_memset(0, 0, 480UL * 272UL);   // clear the bitmap
  GD.Clear();                           // draw the bitmap

  GD.ColorRGB(0x101020);
  GD.cmd_text(240, 136, 31, OPT_CENTER, "sketch demo");

  GD.BitmapLayout(L8, 480, 272);
  GD.BitmapSize(NEAREST, BORDER, BORDER, 480, 272);
  GD.Begin(BITMAPS);
  GD.ColorRGB(0xffffff);
  GD.Vertex2ii(0, 0);
  GD.swap();
  GD.cmd_sketch(0, 0, 480, 272, 0, L8); // start sketching
  GD.finish();                          // flush all commands
}

void loop() { }
