void MainMenu(){
 while(1) {
   GD.get_inputs();   
   GD.Clear();
   GD.ColorA(255); 
   
     GD.SaveContext();     
     fondoJPGZoom();
     GD.RestoreContext();

   GD.LineWidth(48);
   GD.Begin(RECTS);
   GD.ColorRGB(0xffffff);
   for (int j = 0; j < Numrects; j++) {
   int y = 40 * j - ymov;
      GD.ColorA(100);
      GD.Tag(j+10);
      GD.Vertex2f(16 * 140, 16 * (y + 6));
      GD.Vertex2f(16 * 240, 16 * (y + 40 - 6));
    }

   GD.ColorA(255);    
   GD.ColorRGB(0xff0000);
   for (int j = 0; j < Numrects; j++) {
   int y = 40 * j - ymov;
        GD.Tag(j+10);
        sprintf(TX,"%d", j+1); GD.cmd_text(180, y+2, 25, 0, TX);   
    }    
    
//    GD.ColorA(15); 
    GD.ColorA(75); 
    GD.Tag(1);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(260, 10, 100, 75, 30, 0,  "Up");    

    if (GD.inputs.tag==1){
          GD.cmd_button(260, 10, 100, 75, 30, OPT_FLAT,  "Up");    
          Y=Y-8; 
          if (Y<-480){Y=480;}
      }    
    
    GD.Tag(2);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(260, 120, 100, 75, 30, 0,  "Dw");    

    if (GD.inputs.tag==2){
          GD.cmd_button(260, 120, 100, 75, 30, OPT_FLAT,  "Dw");              
          Y=Y+8; 
          if (Y>=488){Y=-480;}
      }  

    GD.Tag(3);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(140, 70, 100, 75, 30, 0,  "Left");    

    if (GD.inputs.tag==3){
          GD.cmd_button(140, 70, 100, 75, 30, OPT_FLAT,  "Left");    
          X=X-8; 
          if (X<-800){X=800;}
      }    

    GD.Tag(4);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(680, 70, 100, 75, 30, 0,  "Right");    

    if (GD.inputs.tag==4){
          GD.cmd_button(680, 70, 100, 75, 30, OPT_FLAT,  "Right");
          X=X+8; 
          if (X>=810){X=-800;}
      }    


    GD.Tag(5);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(10, 90, 100, 75, 30, 0,  "Zoom+");    

    if (GD.inputs.tag==5){
          GD.cmd_button(10, 90, 100, 75, 30, OPT_FLAT,  "Zoom+");
          zoom=zoom+0.05; 
          if (zoom>=3.5){zoom=3.5;}
      }


    GD.Tag(6);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(10, 180, 100, 75, 30, 0,  "Zoom-");    

    if (GD.inputs.tag==6){
          GD.cmd_button(10, 180, 100, 75, 30, OPT_FLAT,  "Zoom-");
          zoom=zoom-0.05; 
          if (zoom<=0.05){zoom=0.05;}
      }

//JPG menu
    GD.Tag(7);   
    if (GD.inputs.tag==7){
          MenuP();    
      }


    GD.Tag(8);
   // GD.ColorA(25); 
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(315, 205, 50, 35, 26, 0,  "Up");    
    if (GD.inputs.tag==8){
          GD.cmd_button(315, 205, 50, 35, 26, OPT_FLAT,  "Up");
          ymov = ymov + 8; 
          if (ymov>= 598){ymov=-480;}
      }


    GD.Tag(9);
    GD.cmd_fgcolor(0x00ff00); 
    GD.ColorRGB(0x000000);     
    GD.cmd_button(260, 225, 50, 35, 26, 0,  "Dw");    
    if (GD.inputs.tag==9){
          GD.cmd_button(260, 225, 50, 35, 26, OPT_FLAT,  "Dw");
          ymov = ymov - 8; 
          if (ymov<=-480){ymov=598;}
      }

    GD.Tag(10);   
    if (GD.inputs.tag==10){
          Menu1();    
      }

    GD.Tag(11); 
    if (GD.inputs.tag==11){
          Menu2();    
      }


    GD.Tag(12);  
    if (GD.inputs.tag==12){
          Menu3();    
      }


    GD.Tag(13);   
    if (GD.inputs.tag==13){
          Menu4();    
      }


    GD.Tag(14);
    if (GD.inputs.tag==14){
          Menu5();    
      }

    GD.Tag(15);  
    if (GD.inputs.tag==15){
          Menu6();    
      }


    GD.Tag(16);  
    if (GD.inputs.tag==16){
          Menu7();    
      }


    GD.Tag(17); 
    if (GD.inputs.tag==17){
          Menu8();    
      }


    GD.Tag(18);  
    if (GD.inputs.tag==18){
          Menu9();    
      }


   GD.Tag(255);  
   GD.ColorA(255);      
//   GD.ColorRGB(0,255,0); sprintf(TX,"%d", X); GD.cmd_text(270, 200, 31, 0, TX);   
//   GD.ColorRGB(0,255,0); sprintf(TX,"%d", Y); GD.cmd_text(350, 200, 31, 0, TX);
     GD.ColorRGB(255,255,255);     plotfloat(20, 230, zoom, 2);
     GD.ColorRGB(255,255,255);     plotfloat(420, 230, zoom, 3);     
     GD.ColorRGB(255,255,255);     plotfloat(210, 230, zoom, 1);               
   GD.swap();
 }
}
