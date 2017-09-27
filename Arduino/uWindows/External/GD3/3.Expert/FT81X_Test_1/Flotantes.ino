static void plotfloat(int x, int y, float f, int Ndec, int fontsize)
{
  GD.cmd_number(x - 2, y, fontsize, OPT_RIGHTX | OPT_SIGNED, int(f));
  GD.cmd_text(  x,     y, fontsize, 0, ".");
 if (Ndec==1){
  GD.cmd_number(x + 8, y, fontsize, Ndec, int(10 * abs(f))); // 1 decimal
  }  
 if (Ndec==2){
  GD.cmd_number(x + 8, y, fontsize, Ndec, int(100 * abs(f))); // 2 decimal
  }
 if (Ndec==3){  
  GD.cmd_number(x + 8, y, fontsize, Ndec, int(1000 * abs(f))); //3 decimal
  }
}
