/*
 Name:		ArduinoEngine.ino
 Created:	9/28/2017 8:37:22 AM
 Author:	rohme
*/

#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include "UIManager.h"

UIManager *uiMan;

// the setup function runs once when you press reset or power the board
void setup() {
	uiMan = new UIManager();
}

// the loop function runs over and over again until power down or reset
void loop() {
	uiMan->Update();
}
