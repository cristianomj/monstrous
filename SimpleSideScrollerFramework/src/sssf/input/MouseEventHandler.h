/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	MouseEventHandler.h

	This class provides a framework for mouse event handlers. It is assumed
	that each game application will have different mappings and different
	types of responses to mouse presses on the game world. That custom behavior
	must be programmed in cooperation with the indiviual game application.
	
	Child classes would put their custom responses inside the handleMouseEvents method,
	which is called by the GameInput method every time a mouse click is encountered.
*/

#pragma once
#include "sssf_VS\stdafx.h"

class Game;

class MouseEventHandler
{
protected:
	// INLINED CONSTRUCTOR
	MouseEventHandler(){}

	 // INLINED DESTRUCTOR
	~MouseEventHandler(){}

public:
	// METHOD DEFINED IN GAME-SPECIFIC CHILD CLASSES
	virtual void handleMousePressEvent(Game *game, int mouseX, int mouseY)=0;
	virtual void handleMouseMoveEvent(Game *game, int mouseX, int mouseY)=0;
};