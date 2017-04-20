#include "Debug.h"
#include "BaseItems/WindowManager.h"

WindowManager *wm;

extern "C"{
  int _getpid(){ return -1;}
  int _kill(int pid, int sig){ return -1; }
  int _write(){return -1;}
}

void setup()
{

	wm=WindowManager::instance(Rectangle(0,0,799,479),10,9);
}

void loop()
{

}
