#include "bugs_VS\stdafx.h"
#include "bugs\BugsMouseEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Viewport.h"

void BugsMouseEventHandler::handleMousePressEvent(Game *game, int mouseX, int mouseY)
{
	if (game->getGSM()->isGameInProgress())
	{
		Viewport *viewport = game->getGUI()->getViewport();
		
		// DETERMINE WHERE ON THE MAP WE HAVE CLICKED
		int worldCoordinateX = mouseX + viewport->getViewportX();
		int worldCoordinateY = mouseY + viewport->getViewportY();

		// NOW LET'S SEND THE PLAYER THERE
		SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
		TopDownSprite *player = spriteManager->getPlayer();
		GridPathfinder *pathfinder = spriteManager->getPathfinder();
		pathfinder->mapPath(player, (float)worldCoordinateX, (float)worldCoordinateY);
	}
}

void BugsMouseEventHandler::handleMouseMoveEvent(Game *game, int mouseX, int mouseY)
{
	// DETERMINE WHAT THE PATHFINDING GRID CELL
	// IS THAT THE MOUSE CURRENTLY IS ABOVE
	if (game->getGSM()->isGameInProgress())
	{
		// IF YOU LIKE YOU COULD DO SOME MOUSE OVER DEBUGGING STUFF HERE
	}
}