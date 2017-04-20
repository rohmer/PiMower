/*
 Name:		UILibrary.ino
 Created:	4/18/2017 11:40:27 AM
 Author:	rohme
 Editor:	http://www.visualmicro.com
*/
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <ArduinoSTL.h>
#include <SerialDebug.h>
#include <PrintCascade.h>
#include "BaseItems\WindowManager.h"
#include "Rectangle.h"

// the setup function runs once when you press reset or power the board
void setup() {
	WindowManager *wm = WindowManager::instance(Rectangle(0, 0, 800, 480), 10, 9);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
