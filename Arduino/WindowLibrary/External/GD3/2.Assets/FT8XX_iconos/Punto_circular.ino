const int noiconos=11;
float cx=200, cy=100, r=95, tetha=0, Cx[noiconos], Cy[noiconos], Tetha[noiconos], Cx1[noiconos], Cy1[noiconos], Tetha1[noiconos];
float Px[noiconos], Py[noiconos], Px1[noiconos], Py1[noiconos], deltatetha=2, pi=3.141592654;

float Cx2[noiconos], Cy2[noiconos], Tetha2[noiconos];
float Px2[noiconos], Py2[noiconos];

float Cx3[noiconos], Cy3[noiconos], Tetha3[noiconos];
float Px3[noiconos], Py3[noiconos];

void PCircular()
{
  espera();
  LOAD_ASSETS0();  
  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  GD.load("zx20.jpg");  //si lo carga XD  480x156  
  
 
for (int i=0; i<noiconos; i++)
{
  Cx[i]=random(r,480-r);
  Cy[i]=random(r,272-r);
  Tetha[i]=random(0,359);  

  Cx1[i]=random(r,480-r);
  Cy1[i]=random(r,272-r);
  Tetha1[i]=random(0,359);  
  
  Cx2[i]=random(r,480-r);
  Cy2[i]=random(r,272-r);
  Tetha2[i]=random(0,359);    

  Cx3[i]=random(r,480-r);
  Cy3[i]=random(r,272-r);
  Tetha3[i]=random(0,359);      
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
 }  
  while(1)
  {
//   GD.ClearColorRGB(0x000000);  
   GD.Clear();
   GD.Begin(BITMAPS);
   GD.Vertex2ii(0, 95, 15);   //Imagen de fondo de  480x156



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
      }  
   GD.RestoreContext();  
   GD.swap();       
  }
} 



void PCircular1()
{
  espera();
  LOAD_ASSETS0();  
  
  Px[1]= cx + r*(cos(pi*tetha/180));
  Py[1]= cy + r*(sin(pi*tetha/180));

 while(1)
 {
   GD.ClearColorRGB(0x000000);  
   GD.Clear();
   GD.Begin(BITMAPS);

   GD.SaveContext();     
   icon3Zoom(0.4);   // escala 0.5 XD de cualquier icono XD del set de iconos desplegado
      tetha=tetha+deltatetha;  
      if (tetha>=360){tetha=0;}
       Px[1]= cx + r*(cos(pi*tetha/180));
       Py[1]= cy + r*(sin(pi*tetha/180));           
       GD.Vertex2ii(Px[1], Py[1], 11);
   GD.RestoreContext();  
   GD.swap();       
  }
} 



