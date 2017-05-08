/*
 Name:		UILibrary.ino
 Created:	4/18/2017 11:40:27 AM
 Author:	rohme
 Editor:	http://www.visualmicro.com
*/
#include <utility.h>

#include "BaseItems\WindowManager.h"
#include "Rectangle.h"
WindowManager *wm=NULL;

// the setup function runs once when you press reset or power the board
void setup() {
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (wm == NULL)
	{
		wm = WindowManager::instance( 10, 9);		
	}
	if(wm!=NULL)
	{
		
	}
}
