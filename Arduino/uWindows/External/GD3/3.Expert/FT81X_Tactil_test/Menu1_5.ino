void Menu1()
{
  while(1)    
  {
   GD.ClearColorRGB(0x000000); 
   GD.Clear();
   GD.ColorRGB(0xffffff);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 1");
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



void Menu2()
{
  while(1)    
  {
   GD.ClearColorRGB(0x000000); 
   GD.Clear();
   GD.ColorRGB(0xFFFFFF);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 2");
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


void Menu3()
{
  while(1)    
  {
   GD.ClearColorRGB(0x00ff00); 
   GD.Clear();
   GD.ColorRGB(0x000000);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 3");
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


void Menu4()
{
  while(1)    
  {
   GD.ClearColorRGB(0x000000); 
   GD.Clear();
   GD.ColorRGB(0xFFFFFF);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 4");
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


void Menu5()
{
  while(1)    
  {
   GD.ClearColorRGB(0x00ff00); 
   GD.Clear();
   GD.ColorRGB(0x000000);
   GD.cmd_text(240, 30, 31, OPT_CENTER, "Menu 5");
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
