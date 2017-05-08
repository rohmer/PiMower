void MenuP()
{
  while(1)    
  {
   GD.Clear();
   GD.Begin(BITMAPS);
   GD.Vertex2ii(0, 0);
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
