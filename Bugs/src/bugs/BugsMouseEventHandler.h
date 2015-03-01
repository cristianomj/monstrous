#pragma once

#include "sssf\game\Game.h"
#include "sssf\input\MouseEventHandler.h"

class BugsMouseEventHandler : public MouseEventHandler
{
public:
	BugsMouseEventHandler() {}
	~BugsMouseEventHandler() {}
	void handleMousePressEvent(Game *game, int mouseX, int mouseY);
	void handleMouseMoveEvent(Game *game, int mouseX, int mouseY);
};