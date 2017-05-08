const int noiconos=11;
float cx=200, cy=100, r=95, tetha=0, Cx[noiconos], Cy[noiconos], Tetha[noiconos], Cx1[noiconos], Cy1[noiconos], Tetha1[noiconos];
float Px[noiconos], Py[noiconos], Px1[noiconos], Py1[noiconos], pi=3.141592654;

float deltatetha=1.3;
//float deltatetha=1.2;
//float deltatetha=1.9;


float Cx2[noiconos], Cy2[noiconos], Tetha2[noiconos];
float Px2[noiconos], Py2[noiconos];

float Cx3[noiconos], Cy3[noiconos], Tetha3[noiconos];
float Px3[noiconos], Py3[noiconos];

float Cx4[noiconos], Cy4[noiconos], Tetha4[noiconos];
float Px4[noiconos], Py4[noiconos];

float Cx5[noiconos], Cy5[noiconos], Tetha5[noiconos];
float Px5[noiconos], Py5[noiconos];

//float Cx6[noiconos], Cy6[noiconos], Tetha6[noiconos];
//float Px6[noiconos], Py6[noiconos];

//float Cx7[noiconos], Cy7[noiconos], Tetha7[noiconos];
//float Px7[noiconos], Py7[noiconos];

//float Cx8[noiconos], Cy8[noiconos], Tetha8[noiconos];
//float Px8[noiconos], Py8[noiconos];

//float Cx9[noiconos], Cy9[noiconos], Tetha9[noiconos];
//float Px9[noiconos], Py9[noiconos];

//float Cx10[noiconos], Cy10[noiconos], Tetha10[noiconos];
//float Px10[noiconos], Py10[noiconos];

float contador=0;
int TextS= 27;
int PX=650;


void MCircular()
{
  espera();
  LOAD_ASSETS0();  
  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
 // GD.load("zx20.jpg");  
  GD.load("Fn1.jpg");  //si lo carga XD  800x480

 
for (int i=0; i<noiconos; i++)
{
  Cx[i]=random(r,510-r);
  Cy[i]=random(r,480-r);
  Tetha[i]=random(0,359);  

  Cx1[i]=random(r,510-r);
  Cy1[i]=random(r,480-r);
  Tetha1[i]=random(0,359);  
  
  Cx2[i]=random(r,510-r);
  Cy2[i]=random(r,480-r);
  Tetha2[i]=random(0,359);    

  Cx3[i]=random(r,510-r);
  Cy3[i]=random(r,480-r);
  Tetha3[i]=random(0,359);      

  Cx4[i]=random(r,510-r);
  Cy4[i]=random(r,480-r);
  Tetha4[i]=random(0,359);    

  Cx5[i]=random(r,510-r);
  Cy5[i]=random(r,480-r);
  Tetha5[i]=random(0,359);        

//  Cx6[i]=random(r,510-r);
//  Cy6[i]=random(r,480-r);
//  Tetha6[i]=random(0,359);      

//  Cx7[i]=random(r,480-r);
//  Cy7[i]=random(r,272-r);
//  Tetha7[i]=random(0,359);    

//  Cx8[i]=random(r,480-r);
//  Cy8[i]=random(r,272-r);
//  Tetha8[i]=random(0,359);          

//  Cx9[i]=random(r,480-r);
//  Cy9[i]=random(r,272-r);
//  Tetha9[i]=random(0,359);    

//  Cx10[i]=random(r,480-r);
//  Cy10[i]=random(r,272-r);
//  Tetha10[i]=random(0,359);            
}  

for (int i=0; i<noiconos; i++)
 {  
  Px[i]= Cx[i] + r*(cos(pi*Tetha[i]/180));
  Py[i]= Cy[i] + r*(sin(pi*Tetha[i]/180));

  Px1[i]= Cx1[i] + r*(cos(pi*Tetha1[i]/180));
  Py1[i]= Cy1[i] + r*(sin(pi*Tetha1[i]/180));  

  Px2[i]= Cx2[i] + r*(cos(pi*Tetha2[i]/180));
  Py2[i]= Cy2[i] + r*(sin(pi*Tetha2[i]/180));  

  Px3[i]= Cx3[i] + r*(cos(pi*Tetha3[i]/180));
  Py3[i]= Cy3[i] + r*(sin(pi*Tetha3[i]/180));  

  Px4[i]= Cx4[i] + r*(cos(pi*Tetha4[i]/180));
  Py4[i]= Cy4[i] + r*(sin(pi*Tetha4[i]/180));  

  Px5[i]= Cx5[i] + r*(cos(pi*Tetha5[i]/180));
  Py5[i]= Cy5[i] + r*(sin(pi*Tetha5[i]/180));  
  
//  Px6[i]= Cx6[i] + r*(cos(pi*Tetha6[i]/180));
//  Py6[i]= Cy6[i] + r*(sin(pi*Tetha6[i]/180));  

//  Px7[i]= Cx7[i] + r*(cos(pi*Tetha7[i]/180));
//  Py7[i]= Cy7[i] + r*(sin(pi*Tetha7[i]/180));  

//  Px8[i]= Cx8[i] + r*(cos(pi*Tetha8[i]/180));
//  Py8[i]= Cy8[i] + r*(sin(pi*Tetha8[i]/180));  

//  Px9[i]= Cx9[i] + r*(cos(pi*Tetha9[i]/180));
//  Py9[i]= Cy9[i] + r*(sin(pi*Tetha9[i]/180));  

//  Px10[i]= Cx10[i] + r*(cos(pi*Tetha10[i]/180));
//  Py10[i]= Cy10[i] + r*(sin(pi*Tetha10[i]/180));  
 }

  while(1)
  {
//   GD.ClearColorRGB(0x000000);  
   GD.Clear();
   
 GD.SaveContext();  
  GD.Begin(RECTS);  GD.LineWidth(25);  GD.ColorRGB(0x000000); //GD.ColorRGB(0x001010);
  GD.Vertex2f(0*16, 0*16);  
  GD.Vertex2f(800*16, 480*16);  
  GD.End();  
 GD.RestoreContext();    

 GD.SaveContext();  
  GD.Begin(LINES);  GD.LineWidth(25); GD.ColorRGB(0x00ff00);  
    GD.Vertex2f(1*16, 479*16); GD.Vertex2f(799*16, 1*16);
    GD.Vertex2f(1*16, 1*16); GD.Vertex2f(799*16, 479*16);    
    GD.Vertex2f(1*16, 1*16); GD.Vertex2f(799*16, 1*16);    
    GD.Vertex2f(799*16, 1*16); GD.Vertex2f(799*16, 479*16);    
    GD.Vertex2f(1*16, 479*16); GD.Vertex2f(799*16, 479*16);    
    GD.Vertex2f(1*16, 1*16); GD.Vertex2f(1*16, 479*16);        
  GD.End();
 GD.RestoreContext();    
   
   GD.Begin(BITMAPS);
//   GD.Vertex2ii(315, 300, 15);   //Imagen de fondo de  480x156
 GD.ColorA(100); 
   GD.Vertex2ii(0, 0, 15);   //Imagen de fondo de  800x480
 GD.ColorA(255); 
 
   GD.Vertex2ii(500, 300, 1);  //si se dibuja
   GD.Vertex2ii(600, 300, 1);    //no se dibuja


   GD.SaveContext();     
   icon3Zoom(0.3);
      for (int i=0; i<noiconos; i++)
      {  
      Tetha[i]=Tetha[i]+deltatetha;  
      if (Tetha[i]>=360){Tetha[i]=0;}        
       Px[i]= Cx[i] + r*(cos(pi*Tetha[i]/180));
       Py[i]= Cy[i] + r*(sin(pi*Tetha[i]/180));           
       GD.Vertex2ii(Px[i], Py[i], i);

      Tetha1[i]=Tetha1[i]+deltatetha;  
      if (Tetha1[i]>=360){Tetha1[i]=0;}        
       Px1[i]= Cx1[i] + r*(cos(pi*Tetha1[i]/180));
       Py1[i]= Cy1[i] + r*(sin(pi*Tetha1[i]/180));           
       GD.Vertex2ii(Px1[i], Py1[i], i);       

      Tetha2[i]=Tetha2[i]+deltatetha;  
      if (Tetha2[i]>=360){Tetha2[i]=0;}        
       Px2[i]= Cx2[i] + r*(cos(pi*Tetha2[i]/180));
       Py2[i]= Cy2[i] + r*(sin(pi*Tetha2[i]/180));           
       GD.Vertex2ii(Px2[i], Py2[i], i);       

      Tetha3[i]=Tetha3[i]-deltatetha;  
      if (Tetha3[i]<=-360){Tetha3[i]=0;}        
       Px3[i]= Cx3[i] + r*(cos(pi*Tetha3[i]/180));
       Py3[i]= Cy3[i] + r*(sin(pi*Tetha3[i]/180));           
       GD.Vertex2ii(Px3[i], Py3[i], i);       

      Tetha4[i]=Tetha4[i]+deltatetha;  
      if (Tetha4[i]>=360){Tetha4[i]=0;}        
       Px4[i]= Cx4[i] + r*(cos(pi*Tetha4[i]/180));
       Py4[i]= Cy4[i] + r*(sin(pi*Tetha4[i]/180));           
       GD.Vertex2ii(Px4[i], Py4[i], i);       

      Tetha5[i]=Tetha5[i]-deltatetha;  
      if (Tetha5[i]<=-360){Tetha5[i]=0;}        
       Px5[i]= Cx5[i] + r*(cos(pi*Tetha5[i]/180));
       Py5[i]= Cy5[i] + r*(sin(pi*Tetha5[i]/180));           
       GD.Vertex2ii(Px5[i], Py5[i], i);       

//      Tetha6[i]=Tetha6[i]-deltatetha;  
//      if (Tetha6[i]<=-360){Tetha6[i]=0;}        
//       Px6[i]= Cx6[i] + r*(cos(pi*Tetha6[i]/180));
//       Py6[i]= Cy6[i] + r*(sin(pi*Tetha6[i]/180));           
//       GD.Vertex2ii(Px6[i], Py6[i], i);       

//      Tetha7[i]=Tetha7[i]+deltatetha;  
//      if (Tetha7[i]>=360){Tetha7[i]=0;}        
//       Px7[i]= Cx7[i] + r*(cos(pi*Tetha7[i]/180));
//       Py7[i]= Cy7[i] + r*(sin(pi*Tetha7[i]/180));           
//       GD.Vertex2ii(Px7[i], Py7[i], i);       

//      Tetha8[i]=Tetha8[i]-deltatetha;  
//      if (Tetha8[i]<=-360){Tetha8[i]=0;}        
//       Px8[i]= Cx8[i] + r*(cos(pi*Tetha8[i]/180));
//       Py8[i]= Cy8[i] + r*(sin(pi*Tetha8[i]/180));           
//       GD.Vertex2ii(Px8[i], Py8[i], i);       
       
//      Tetha9[i]=Tetha9[i]+deltatetha;  
//      if (Tetha9[i]>=360){Tetha9[i]=0;}        
//       Px9[i]= Cx9[i] + r*(cos(pi*Tetha9[i]/180));
//       Py9[i]= Cy9[i] + r*(sin(pi*Tetha9[i]/180));           
 //      GD.Vertex2ii(Px9[i], Py9[i], i);       

 //     Tetha10[i]=Tetha10[i]-deltatetha;  
 //     if (Tetha10[i]<=-360){Tetha10[i]=0;}        
 //      Px10[i]= Cx10[i] + r*(cos(pi*Tetha10[i]/180));
 //      Py10[i]= Cy10[i] + r*(sin(pi*Tetha10[i]/180));           
 //      GD.Vertex2ii(Px10[i], Py10[i], i);              
      }  
   GD.RestoreContext();  

//medidor de tiempo
  unsigned long currentMillis = millis();        
  if(currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
     contador = contador +1;
  }   
//medidor de tiempo  

 GD.SaveContext();  
  GD.Begin(POINTS);  GD.PointSize(16 * 25);
  //GD.Vertex2ii(800, 0);         //no se dibuja
  GD.Vertex2f(800*16, 300*16);  //si se dibuja
  GD.Vertex2f(800*16, 480*16);  //si se dibuja
 GD.RestoreContext();  

 GD.ColorRGB(0xffff00);  
   //plotfloat(75, 255, contador, 1, TextS);
   GD.cmd_number(100, 255, TextS, OPT_RIGHTX | OPT_SIGNED, contador);   //segundos
   GD.cmd_number(760, 450, TextS, OPT_RIGHTX | OPT_SIGNED, contador);   //segundos
   GD.ColorRGB(0xffffff);  plotfloat(175, 255, contador/60, 1, TextS);  //minutos     
   GD.ColorRGB(0xffffff);  plotfloat(250, 255, (contador/60)/60, 2, TextS);  //horas
   GD.ColorRGB(0xffffff);  plotfloat(325, 255, ((contador/60)/60)/24, 3, TextS);  //días   
 //GD.cmd_clock(650,136,130,0,8,41,39,0);
  
   Poligono();
   
   GD.swap();       
  }
}





