#define Seguidor1  201
#define Seguidor2  202

int Valor1=125,  Valor2=125;

void slider2()
{
//Horizontal: izquierda a derecha
  GD.SaveContext();
  GD.Tag(Seguidor1);
  GD.cmd_fgcolor(0xff0000);                          //color del deslizador
//  GD.ColorRGB(0x000000);   GD.cmd_bgcolor(0x0000ff); //color de la base  
  GD.ColorRGB(0x000000);  GD.cmd_bgcolor(0x000000); //color de la base

  GD.cmd_slider(PXS,95,200,20,OPT_FLAT,Valor1,255);
  //            x,   y,  largo, espesor, tag a seguir 
  GD.cmd_track( PXS,95,200,20,Seguidor1);

  switch (GD.inputs.track_tag & 0xff) {
  case Seguidor1:
    Valor1 = GD.inputs.track_val * 255L / 65535;    //Horizontal: izquierda a derecha
    //Valor1 = 255-(GD.inputs.track_val * 255L / 65535);    //Vertical: arriba a abajo  
    Serial.println(Valor1);
    break;
    }
  GD.RestoreContext();
//Horizontal: izquierda a derecha

//Vertical: arriba a abajo  
  GD.SaveContext();  
  GD.Tag(Seguidor2);  
  GD.cmd_fgcolor(0x00ff00);                         //color del deslizador
  //GD.ColorRGB(0x0000ff);  GD.cmd_bgcolor(0x000000); //color de la base
  GD.ColorRGB(0x000000);  GD.cmd_bgcolor(0x000000); //color de la base

  GD.cmd_slider(20,200,20,200,OPT_FLAT,255-Valor2,255);
  //            x,   y,  largo, espesor, tag a seguir 
  GD.cmd_track( 20,200,20,200,Seguidor2);  

  switch (GD.inputs.track_tag & 0xff) {
  case Seguidor2:
   // Valor2 = GD.inputs.track_val * 255L / 65535;    //Horizontal: izquierda a derecha
    Valor2 = 255-(GD.inputs.track_val * 255L / 65535);    //Vertical: arriba a abajo  
    Serial.println(Valor2);
    break;    
   }
  GD.RestoreContext();
//Vertical: arriba a abajo  
  
  GD.ColorRGB(0xffffff);   GD.cmd_number(PX, 10+10+50, 28, OPT_RIGHTX | OPT_SIGNED, Valor1);   
  GD.ColorRGB(0xffffff);   GD.cmd_number(100, 400, 28, OPT_RIGHTX | OPT_SIGNED, Valor2);     
}
