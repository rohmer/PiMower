void Ciclo()
{
  start = millis();       
  GD.cmd_loadimage(0, 0);
  GD.load("Ab1.jpg");
  CargaJPG();  

  start = millis();       
  GD.cmd_loadimage(0, 0);
  GD.load("Ab2.jpg");
  CargaJPG();

  start = millis();       
  GD.cmd_loadimage(0, 0);
  GD.load("Ab3.jpg");
  CargaJPG();

  start = millis();       
  GD.cmd_loadimage(0, 0);
  GD.load("Ab4.jpg");
  CargaJPG();

  start = millis();       
  GD.cmd_loadimage(0, 0);
  GD.load("Ab5.jpg");
  CargaJPG();
}  
