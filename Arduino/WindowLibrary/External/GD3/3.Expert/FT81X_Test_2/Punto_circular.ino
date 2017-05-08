//const int noiconos=11;
const int noiconos=2;
float cx=200, cy=200, r=95, tetha=0, Cx[noiconos], Cy[noiconos], Tetha[noiconos], Cx1[noiconos], Cy1[noiconos], Tetha1[noiconos];
float Px[noiconos], Py[noiconos], Px1[noiconos], Py1[noiconos], deltatetha=2, pi=3.141592654;

float Cx2[noiconos], Cy2[noiconos], Tetha2[noiconos];
float Px2[noiconos], Py2[noiconos];

float Cx3[noiconos], Cy3[noiconos], Tetha3[noiconos];
float Px3[noiconos], Py3[noiconos];

float Cx4[noiconos], Cy4[noiconos], Tetha4[noiconos];
float Px4[noiconos], Py4[noiconos];

float Cx5[noiconos], Cy5[noiconos], Tetha5[noiconos];
float Px5[noiconos], Py5[noiconos];

float Cx6[noiconos], Cy6[noiconos], Tetha6[noiconos];
float Px6[noiconos], Py6[noiconos];

float Cx7[noiconos], Cy7[noiconos], Tetha7[noiconos];
float Px7[noiconos], Py7[noiconos];

float Cx8[noiconos], Cy8[noiconos], Tetha8[noiconos];
float Px8[noiconos], Py8[noiconos];


void Test2()
{
  espera();
  LOAD_ASSETS1();  
  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  GD.load("Fn1.jpg");  //si lo carga XD  800x480  
  

  Tetha[1]=random(0,359);    
  Px[1]= cx + r*(cos(pi*Tetha[1]/180));
  Py[1]= cy + r*(sin(pi*Tetha[1]/180));

  Tetha2[1]=random(0,359);    
  Px2[1]= cx + 135*(cos(pi*Tetha2[1]/180));
  Py2[1]= cy + 135*(sin(pi*Tetha2[1]/180));

  Tetha3[1]=random(0,359);    
  Px3[1]= cx + 175*(cos(pi*Tetha3[1]/180));
  Py3[1]= cy + 175*(sin(pi*Tetha3[1]/180)); 

  Tetha4[1]=random(0,359);    
  Px4[1]= cx + 135*(cos(pi*Tetha4[1]/180));
  Py4[1]= cy + 135*(sin(pi*Tetha4[1]/180));   
  
  Tetha5[1]=random(0,359);    
  Px5[1]= cx + 175*(cos(pi*Tetha5[1]/180));
  Py5[1]= cy + 175*(sin(pi*Tetha5[1]/180));   
  
  Tetha6[1]=random(0,359);    
  Px6[1]= cx + r*(cos(pi*Tetha6[1]/180));
  Py6[1]= cy + r*(sin(pi*Tetha6[1]/180));     
  
  Tetha7[1]=random(0,359);    
  Px7[1]= cx + 155*(cos(pi*Tetha7[1]/180));
  Py7[1]= cy + 155*(sin(pi*Tetha7[1]/180));   
  
  Tetha8[1]=random(0,359);    
  Px8[1]= cx + 155*(cos(pi*Tetha8[1]/180));
  Py8[1]= cy + 155*(sin(pi*Tetha8[1]/180));       

int Xbase = 0, velX = 10;

 while(1)
 {
   GD.ClearColorRGB(0x000000);  
   GD.Clear();
   GD.Begin(BITMAPS);

  GD.Vertex2ii(0, 0, 15);   //800x450 px


   Xbase = Xbase + velX;
   
   if(Xbase ==300){velX=-10;}
   if(Xbase ==0){velX=10;}   
   
   GD.VertexTranslateX(16*Xbase); //mueve componente x de vertex2ii 300 pixeles a la derecha XD
   
   
   GD.SaveContext();     
     icon3Zoom(1.0);   
     GD.Vertex2ii(cx-15, cy-15, 0);
   GD.RestoreContext();     

   GD.SaveContext();     
   icon3Zoom(0.6);   // escala a 60% 
      Tetha[1]=Tetha[1]+deltatetha;  
      if (Tetha[1]>=360){Tetha[1]=0;}
       Px[1]= cx + r*(cos(pi*Tetha[1]/180));
       Py[1]= cy + r*(sin(pi*Tetha[1]/180));           
       GD.Vertex2ii(Px[1], Py[1], 1);
       
      Tetha2[1]=Tetha2[1]+deltatetha;  
      if (Tetha2[1]>=360){Tetha2[1]=0;}        
       Px2[1]= cx + 135*(cos(pi*Tetha2[1]/180));
       Py2[1]= cy + 135*(sin(pi*Tetha2[1]/180));           
       GD.Vertex2ii(Px2[1], Py2[1], 1);              
       
      Tetha3[1]=Tetha3[1]-deltatetha;  
      if (Tetha3[1]<=-360){Tetha3[1]=0;}           
       Px3[1]= cx + 175*(cos(pi*Tetha3[1]/180));
       Py3[1]= cy + 175*(sin(pi*Tetha3[1]/180));           
       GD.Vertex2ii(Px3[1], Py3[1], 1);            
       
      Tetha4[1]=Tetha4[1]-deltatetha;  
      if (Tetha4[1]<=-360){Tetha4[1]=0;}           
       Px4[1]= cx + 135*(cos(pi*Tetha4[1]/180));
       Py4[1]= cy + 135*(sin(pi*Tetha4[1]/180));           
       GD.Vertex2ii(Px4[1], Py4[1], 1);

      Tetha5[1]=Tetha5[1]+deltatetha;  
      if (Tetha5[1]>=360){Tetha5[1]=0;}        
       Px5[1]= cx + 175*(cos(pi*Tetha5[1]/180));
       Py5[1]= cy + 175*(sin(pi*Tetha5[1]/180));           
       GD.Vertex2ii(Px5[1], Py5[1], 1);       
       
      Tetha6[1]=Tetha6[1]-deltatetha;  
      if (Tetha6[1]<=-360){Tetha6[1]=0;}           
       Px6[1]= cx + r*(cos(pi*Tetha6[1]/180));
       Py6[1]= cy + r*(sin(pi*Tetha6[1]/180));           
       GD.Vertex2ii(Px6[1], Py6[1], 1);     

      Tetha7[1]=Tetha7[1]-deltatetha;  
      if (Tetha7[1]<=-360){Tetha7[1]=0;}           
       Px7[1]= cx + 155*(cos(pi*Tetha7[1]/180));
       Py7[1]= cy + 155*(sin(pi*Tetha7[1]/180));           
       GD.Vertex2ii(Px7[1], Py7[1], 1);          
       
      Tetha8[1]=Tetha8[1]+deltatetha;  
      if (Tetha8[1]>=360){Tetha8[1]=0;}        
       Px8[1]= cx + 155*(cos(pi*Tetha8[1]/180));
       Py8[1]= cy + 155*(sin(pi*Tetha8[1]/180));           
       GD.Vertex2ii(Px8[1], Py8[1], 1);              
       
   GD.RestoreContext();  
   GD.swap();       
  }
}


