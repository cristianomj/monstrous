/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugsButtonEventHandler.h

	This is a custom button event handler. Each game can choose
	to use different buttons and respond differently to when
	buttons are pressed. This class will handle button presses for
	the BugsGame following the ButtonEventHandler pattern.
*/

#pragma once
#include "bugs_VS\stdafx.h"
#include "sssf\input\ButtonEventHandler.h"

class Game;

class BugsButtonEventHandler: public ButtonEventHandler
{
public:
	// AS-IS, THIS CLASS HAS NO DATA, SO THERE IS NOTHING
	// TO INITIALIZE OR DESTROY
	BugsButtonEventHandler()	{}
	~BugsButtonEventHandler()	{}

	// DEFINED INSIDE BugsButtonEventHandler.cpp
	void handleButtonEvents(Game *game, 
							wstring command);
};