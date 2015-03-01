/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugsKeyEventHandler.h

	This is a custom key event handler. Each game can choose
	to use different keyboard keys and respond differently to when
	they are pressed. This class will handle key presses for
	this particular game following the KeyEventHandler pattern.
*/

#pragma once
#include "bugs_VS\stdafx.h"
#include "sssf\input\KeyEventHandler.h"

class Game;

class BugsKeyEventHandler : public KeyEventHandler
{
public:
	BugsKeyEventHandler()		{}
	~BugsKeyEventHandler()		{}
	void handleKeyEvents(Game *game);
};