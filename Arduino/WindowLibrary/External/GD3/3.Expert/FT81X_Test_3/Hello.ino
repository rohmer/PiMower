void hello()
{
  GD.ClearColorRGB(0x103000);
  GD.Clear();
//  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello world");
  GD.cmd_text(GD.w / 2, GD.h / 2, 27, OPT_CENTER, "SD break out long test");
//   GD.cmd_number((GD.w / 2)-40, (GD.h / 2)+25, 27, 0, GD.w);
   GD.cmd_number((GD.w / 2)-(GD.w / 20), (GD.h / 2)+(GD.h / 20), 27, 0, GD.w);
//   GD.cmd_number((GD.w / 2)+10, (GD.h / 2)+25, 27, 0, GD.h);
   GD.cmd_number((GD.w / 2)+(GD.w / 80), (GD.h / 2)+(GD.h / 20), 27, 0, GD.h);   
//   GD.cmd_text(GD.w / 2, (GD.h / 2)+25, 27, OPT_CENTERX, "x");    
   GD.cmd_text(GD.w / 2, (GD.h / 2)+(GD.h / 20), 27, OPT_CENTERX, "x"); 
  
  
#if (FT_801_ENABLE==1)
 Serial.println("FT800");
#endif


#if (FT_801_ENABLE==1)
 Serial.println("FT801");
#endif

#if (FT_810_ENABLE==1)
 Serial.println("FT810");
#endif

#if (FT_811_ENABLE==1)
 Serial.println("FT811");
#endif

#if (FT_812_ENABLE==1)
 Serial.println("FT812");
#endif

#if (FT_813_ENABLE==1)
 GD.cmd_text(GD.w / 2, (GD.h / 2)+(2*(GD.h / 20)), 27, OPT_CENTERX, "FT813");
#endif     
   
  GD.swap();
}
