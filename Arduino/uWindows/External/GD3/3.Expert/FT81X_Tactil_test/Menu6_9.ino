void Menu6()
{
  while(1)    
  {
   GD.ClearColorRGB(0x000000); 
   GD.Clear();
   GD.ColorRGB(0xFFFFFF);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 6");
   GD.get_inputs();
   
    GD.cmd_fgcolor(0x000050); 
    GD.ColorRGB(0xffffff); 
    GD.Tag(19);
    GD.cmd_button(35, 12, 40, 30, 28, 0,  "MP");    

    if (GD.inputs.tag==19){
          MainMenu();    
      }    
    
   GD.swap(); 
  }
}


void Menu7()
{
  while(1)    
  {
   GD.ClearColorRGB(0x00ff00); 
   GD.Clear();
   GD.ColorRGB(0x000000);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 7");
   GD.get_inputs();
   
    GD.cmd_fgcolor(0x000050); 
    GD.ColorRGB(0xffffff); 
    GD.Tag(19);
    GD.cmd_button(35, 12, 40, 30, 28, 0,  "MP");    

    if (GD.inputs.tag==19){
          MainMenu();    
      }    
    
   GD.swap(); 
  }
}


void Menu8()
{
  while(1)    
  {
   GD.ClearColorRGB(0x000000); 
   GD.Clear();
   GD.ColorRGB(0xFFFFFF);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 8");
   GD.get_inputs();
   
    GD.cmd_fgcolor(0x000050); 
    GD.ColorRGB(0xffffff); 
    GD.Tag(19);
    GD.cmd_button(35, 12, 40, 30, 28, 0,  "MP");    

    if (GD.inputs.tag==19){
          MainMenu();    
      }    
    
   GD.swap(); 
  }
}


void Menu9()
{
  while(1)    
  {
   GD.ClearColorRGB(0x00ff00); 
   GD.Clear();
   GD.ColorRGB(0x000000);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 9");
   GD.get_inputs();
   
    GD.cmd_fgcolor(0x000050); 
    GD.ColorRGB(0xffffff); 
    GD.Tag(19);
    GD.cmd_button(35, 12, 40, 30, 28, 0,  "MP");    

    if (GD.inputs.tag==19){
          MainMenu();    
      }    
    
   GD.swap(); 
  }
}
