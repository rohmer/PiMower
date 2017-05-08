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
  GD.swap();
}
