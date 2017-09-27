void Poligono()
{
 int x, y;
  GD.SaveContext();
  GD.Begin(POINTS);
  GD.ColorRGB(0xffffff); //color del texto
  const char *labels[] = {"Ambiente","Agua","Radiador","CPU back","CPU HIS","HD 3770","SSD 1"};
  int align[7] = { OPT_CENTERX, 0, 0, 0, OPT_RIGHTX, OPT_RIGHTX, OPT_RIGHTX };
  
  for (int i = 0; i < 7; i++) {
    ray(x, y, 16 * 128, i);
    GD.cmd_text(x >> 4, y >> 4, 26, OPT_CENTERY | align[i], labels[i]);
  }
  GD.RestoreContext();   
   
 GD.ColorRGB(220, 220, 200);// lineas de diseño
  GD.LineWidth(8);
  GD.Begin(LINES);
  for (int i = 0; i < 7; i++) {
    GD.Vertex2f(PX*16, 136*16);
    ray(x, y, 16 * 114, i);
    GD.Vertex2f(x, y);
  }
  for (int r = 19; r <= 114; r += 19) {
    GD.Begin(LINE_STRIP);
    for (int i = 0; i < 8; i++) {
      ray(x, y, 16 * r, i);
      GD.Vertex2f(x, y);
    }
  }

  int data[7];
  for (int i = 0; i < 7; i++) {
    int speed[] = { 5, 7, 6, 3, 4, 8, 2 };
    data[i] = 900 + GD.rsin(700, 2 * speed[i] * millis());
  }

    GD.ColorRGB(0,0,185); //R,G,B , color del polígono

  GD.SaveContext();
  GD.ColorA(128);
  Poly po;
  po.begin();
  for (int i = 0; i < 7; i++) {
    ray(x, y, data[i], i);
    po.v(x, y);
  }
  po.draw();
  GD.RestoreContext();

  GD.LineWidth(1 * 16);
  GD.Begin(LINE_STRIP);
  drawdata(data);
  ray(x, y, data[0], 0);
  GD.Vertex2f(x, y);

  GD.Begin(POINTS);
  //GD.ColorRGB(0xffffff);
  GD.ColorRGB(0x00ff00);
  GD.PointSize(3.5 * 16);
  drawdata(data);
  GD.ColorRGB(151,187,205);
  GD.PointSize(2.5 * 16);
  drawdata(data); 
}

static void ray(int &x, int &y, int r, int i)
{
  uint16_t th = 0x8000 + 65536UL * i / 7;
  GD.polar(x, y, r, th);
  x += 16 * PX;
  y += 16 * 136;
}

static void drawdata(int *data)
{
  int x, y;
  for (int i = 0; i < 7; i++) {
    ray(x, y, data[i], i);
    GD.Vertex2f(x, y);
  }
}
