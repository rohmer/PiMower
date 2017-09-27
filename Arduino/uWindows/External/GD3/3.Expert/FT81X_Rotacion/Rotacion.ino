void Rotacion0()
{
  GD.ClearColorRGB(0x250000); //fondo de pantalla
  GD.Clear();
   GD.ColorA(255);  
   GD.cmd_setrotate(0);
   GD.Begin(BITMAPS);     
   contadorT();

  GD.Vertex2ii(20, 55);      
   GD.cmd_text(20, 20, 30, 0, "FT81X: ROTACION 0");
   GD.cmd_fgcolor(0xff0000);     GD.cmd_button(30, 300, 60, 40, 30, 0,  "0");
   GD.cmd_fgcolor(0x000000);     
   GD.cmd_button(110, 300, 60, 40, 30, 0,  "1");   
   GD.cmd_button(190, 300, 60, 40, 30, 0,  "2");      
   GD.cmd_button(270, 300, 60, 40, 30, 0,  "3");  

   GD.SaveContext();
     GD.cmd_romfont(1,31);   //Usa las fuentes adicionales del FT81X: 31, 32, 33, 34
     GD.ColorRGB(0xffff00);   
     GD.cmd_text(20, 335, 1, 0, "Fuente 31"); 
     GD.cmd_number(20, 50, 1, 0, contador);   //segundos     
   GD.RestoreContext();
 GD.swap();    
}  
   
void Rotacion1()
{
  GD.ClearColorRGB(0x250000); //fondo de pantalla
  GD.Clear();
   GD.ColorA(255);  
   GD.cmd_setrotate(1);
   GD.Begin(BITMAPS);     
  contadorT();

  GD.Vertex2ii(20, 55);      
   GD.cmd_text(20, 20, 30, 0, "FT81X: ROTACION 1"); 
   GD.cmd_fgcolor(0x000000);     
   GD.cmd_button(30, 300, 60, 40, 30, 0,  "0");
   GD.cmd_fgcolor(0xff0000);     GD.cmd_button(110, 300, 60, 40, 30, 0,  "1");   
   GD.cmd_fgcolor(0x000000);        
   GD.cmd_button(190, 300, 60, 40, 30, 0,  "2");      
   GD.cmd_button(270, 300, 60, 40, 30, 0,  "3");         

   GD.SaveContext();
     GD.cmd_romfont(1,32);   //Usa las fuentes adicionales del FT81X: 31, 32, 33, 34
     GD.ColorRGB(0xffff00);   
     GD.cmd_text(20, 335, 1, 0, "Fuente 32"); 
     GD.cmd_number(20, 50, 1, 0, contador);   //segundos         
   GD.RestoreContext();
  GD.swap();    
}

void Rotacion2()
{
  GD.ClearColorRGB(0x250000); //fondo de pantalla
  GD.Clear();
   GD.ColorA(255);  
   GD.cmd_setrotate(2);
   GD.Begin(BITMAPS);     
  contadorT();

  GD.Vertex2ii(20, 55);      
   GD.cmd_text(20, 20, 30, 0, "FT81X: ROTACION 2");
   GD.cmd_fgcolor(0x000000); 
   GD.cmd_button(30, 300, 60, 40, 30, 0,  "0");
   GD.cmd_button(110, 300, 60, 40, 30, 0,  "1");   
   GD.cmd_fgcolor(0xff0000);     GD.cmd_button(190, 300, 60, 40, 30, 0,  "2");      
   GD.cmd_fgcolor(0x000000);           
   GD.cmd_button(270, 300, 60, 40, 30, 0,  "3");         
   
   GD.SaveContext();
     GD.cmd_romfont(1,33);   //Usa las fuentes adicionales del FT81X: 31, 32, 33, 34
     GD.ColorRGB(0xffff00);   
     GD.cmd_text(20, 335, 1, 0, "Fuente 33"); 
     GD.cmd_number(20, 50, 1, 0, contador);   //segundos     
   GD.RestoreContext();
  GD.swap();    
}  
   
void Rotacion3()
{
  GD.ClearColorRGB(0x250000); //fondo de pantalla
  GD.Clear();
   GD.ColorA(255);  
   GD.cmd_setrotate(3);
   GD.Begin(BITMAPS);     
  contadorT();

  GD.Vertex2ii(20, 55);      
   GD.cmd_text(20, 20, 30, 0, "FT81X: ROTACION 3");
   GD.cmd_fgcolor(0x000000);    
   GD.cmd_button(30, 300, 60, 40, 30, 0,  "0");
   GD.cmd_button(110, 300, 60, 40, 30, 0,  "1");   
   GD.cmd_button(190, 300, 60, 40, 30, 0,  "2");      
   GD.cmd_fgcolor(0xff0000);  GD.cmd_button(270, 300, 60, 40, 30, 0,  "3");         

   GD.SaveContext();
     GD.cmd_romfont(1,34);   //Usa las fuentes adicionales del FT81X: 31, 32, 33, 34
     GD.ColorRGB(0xffff00);   
     GD.cmd_text(20, 335, 1, 0, "Fuente 34"); 
     GD.cmd_number(20, 50, 1, 0, contador);   //segundos       
   GD.RestoreContext();
  GD.swap();    
}

