/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.cpp

	See SpriteManager.h for a class description.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"

/*
	addSpriteToRenderList - This method checks to see if the sprite
	parameter is inside the viewport. If it is, a RenderItem is generated
	for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	PhysicalProperties *pp = sprite->getPhysicalProperties();
	float rotation = sprite->getRotationInRadians();

	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(	
									pp->getX(),
									pp->getY(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		renderList->addRenderItem(	sprite->getCurrentImageID(),
									pp->round(pp->getX()-viewport->getViewportX()),
									pp->round(pp->getY()-viewport->getViewportY()),
									pp->round(pp->getZ()),
									sprite->getAlpha(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight(),
									rotation);
	}
}

/*
	addSpriteItemsToRenderList - This method goes through all of the sprites,
	including the player sprite, and adds the visible ones to the render list.
	This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(	Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);

		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		botIterator = bots.begin();
		while (botIterator != bots.end())
		{			
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}
	}
}

/*
	addSprite - This method is for adding a new sprite to 
	this sprite manager. Once a sprite is added it can be 
	scheduled for rendering.
*/
void SpriteManager::addBot(Bot *botToAdd)
{
	bots.push_back(botToAdd);
}

/*
	addSpriteType - This method is for adding a new sprite
	type. Note that one sprite type can have many sprites. For
	example, we may say that there may be a "Bunny" type of
	sprite, and specify properties for that type. Then there might
	be 100 different Bunnies each with their own properties, but that
	share many things in common according to what is defined in
	the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size()-1;
}

/*
	clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	//spriteTypes.clear();
	//bots.clear();
}

/*
	getSpriteType - This gets the sprite type object that corresponds
	to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
	unloadSprites - This method removes all artwork from memory that
	has been allocated for game sprites.
*/
void SpriteManager::unloadSprites()
{
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
	/*list<Bot*>::iterator botsIt = bots.begin();
	while (botsIt != bots.end())
	{
		list<Bot*>::iterator tempIt = botsIt;
		botsIt++;
		Bot *botToDelete = (*tempIt);
		delete botToDelete;
	}
	bots.clear();

	vector<AnimatedSpriteType*>::iterator spriteTypesIt = spriteTypes.begin();
	while (spriteTypesIt != spriteTypes.end())
	{
		vector<AnimatedSpriteType*>::iterator tempIt = spriteTypesIt;
		spriteTypesIt++;
		AnimatedSpriteType *astToDelete = (*tempIt);
		delete astToDelete;
	}
	spriteTypes.clear();

	// DELETE THE PATHFINDER IF THERE IS ONE
	if (pathfinder != NULL)
		delete pathfinder;
		*/
}

Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	if (!botToRemove) {
		if (bots.size() >= 10) {
			for (int i = 0; i < 10; i++) bots.pop_back();
		}
	}
	return NULL;
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
}

/*
	update - This method should be called once per frame. It
	goes through all of the sprites, including the player, and calls their
	update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{
	// FIRST LET'S DO THE NECESSARY PATHFINDING
	pathfinder->updatePath(&player);
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		pathfinder->updatePath(bot);
		botIterator++;
	}

	// MODIFIED: VIEWPORT FOLLOWS AVATAR
	GameGUI *gui = game->getGUI();
	Viewport *viewport = gui->getViewport();
	GameInput  *input = game->getInput();

	int playerX = player.getBoundingVolume()->getCenterX();
	int playerY = player.getBoundingVolume()->getCenterY();
	int playerVx = player.getPhysicalProperties()->getVelocityX();
	int playerVy = player.getPhysicalProperties()->getVelocityY();

	int viewportX = viewport->getViewportX();
	int viewportY = viewport->getViewportY();
	int viewportWidth = viewport->getViewportWidth();
	int viewportHeight = viewport->getViewportHeight();
	int viewportCenterX = viewport->getViewportCenterX();
	int viewportCenterY = viewport->getViewportCenterY();
	
	int worldWidth = game->getGSM()->getWorld()->getWorldWidth();
	int worldHeight = game->getGSM()->getWorld()->getWorldHeight();

	int incX = -1, incY = -1;

	// IS PLAYER IS IN THE CENTER OF THE VIEWPORT
	if (viewport->isPlayerCentered(playerX, playerY)) {
		// FOLLOW PLAYER
		if (player.getCurrentState() != L"IDLE")
			viewport->moveViewport(playerVx, playerVy, worldWidth, worldHeight);
	}
	else {
		// IF PLAYER IS FAR FROM CENTER
		// MOVE VIEWPORT TORWARDS PLAYER
		//if (playerX != viewportCenterX && playerY != viewportCenterY) {
			// IF VIEWPORT IS ON THE FAR LEFT (X = 0)
			// AND PLAYER IS MOVING LEFT
			if (playerVx < 0 && viewportX <= 0) incX = 0;
			else if (playerVx > 0 && (viewportX + viewportWidth >= worldWidth)) incX = 0;

			// IF VIEWPORT IS ON THE FAR TOP (Y = 0)
			// AND PLAYER IS MOVING UP
			if (playerVy < 0 && viewportY <= 0) incY = 0;
			else if (playerVy > 0 && (viewportY + viewportHeight >= worldHeight)) incY = 0;

			if (incX != 0) {
				if (playerX - viewportCenterX > 64) incX = 10;
				else if (playerX - viewportCenterX < -64) incX = -10;
			}
			if (incY != 0) {
				if (playerY - viewportCenterY > 64) incY = 10;
				else if (playerY - viewportCenterY < -64) incY = -10;
			}

			if (!(incX == 0 && incY == 0)) {

				if (incX == -1) {
					incX = 0;
				}
				if (incY == -1) {
					incY = 0;
				}

				viewport->moveViewport(incX, incY, worldWidth, worldHeight);
			}	
		//}
	}
	
	// THEN UPDATE THE PLAYER SPRITE ANIMATION FRAME/STATE/ROTATION
	player.updateSprite();

	// NOW UPDATE THE REST OF THE SPRITES ANIMATION FRAMES/STATES/ROTATIONS
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		bot->think(game);
		bot->updateSprite();
		botIterator++;
	}
}

void SpriteManager::makeRandomBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY)
{
	Physics *physics = game->getGSM()->getPhysics();
	RandomJumpingBot *bot = new RandomJumpingBot(physics, 30, 120, 1);	// MODIFIED: CHANGED VELOCITY TO 0
	physics->addCollidableObject(bot);
	PhysicalProperties *pp = bot->getPhysicalProperties();
	pp->setPosition(initX, initY);
	bot->setSpriteType(randomJumpingBotType);
	bot->setCurrentState(L"IDLE");					// MODIFIED: START BOT AT IDDLE
	bot->setAlpha(255);
	addBot(bot);
	bot->affixTightAABBBoundingVolume();
}

void SpriteManager::resetBots(void)
{
	for (list<Bot*>::iterator it = bots.begin();
		it != bots.end(); it++)
	{
		int x = 128 + rand() % 3000;
		int y = 128 + rand() % 3000;
		(*it)->getPhysicalProperties()->incX(200);
	}
}