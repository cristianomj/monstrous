/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.h

	This class manages all of the sprites in a given game level. Note
	that the player sprite is also managed by this class.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\BotRecycler.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\ai\pathfinding\GridPathfinder.h"
#include "sssf\gsm\ai\bots\RandomJumpingBot.h"

class SpriteManager
{
private:
	// NOTE THAT MULTIPLE SPRITES MAY SHARE ARTWORK, SO SPRITE TYPES
	// SPECIFIES A TYPE OF SPRITE, OF WHICH THERE MAY BE MANY INSTANCES
	vector<AnimatedSpriteType*> spriteTypes;

	// THESE ARE THE BOTS IN THE GAME, LIKE ENEMIES, ROCKETS, OR ANYTHING
	// THAT MOVES AROUND AND IS NOT THE PLAYER
	list<Bot*> bots;

	// AND THIS IS THE PLAYER. AS-IS, WE ONLY ALLOW FOR ONE PLAYER AT A TIME
	TopDownSprite player;

	// THE BotRecycler MAKES SURE WE DON'T HAVE TO CONSTRUCT BOTS WHENEVER
	// WE NEED TO SPAWN THEM, INSTEAD IT WILL RECYCLE THEM FOR US
	BotRecycler recyclableBots;

	// THIS GUY HELPS SPRITES FIND THEIR WAY. NOTE THAT IT IS CUSTOMIZABLE, SINCE
	// WE MAY BE RENDERING AN ORTHOGRAPHIC MAP OR AN ISOMETRIC ONE
	GridPathfinder *pathfinder;

public:
	// NOTHING TO INIT OR DESTROY
	SpriteManager()		{}
	~SpriteManager()	{}

	// INLINED ACCESSOR METHODS
	int						getNumberOfSprites()	{ return bots.size();		}
	TopDownSprite*			getPlayer()				{ return &player;			}
	list<Bot*>::iterator	getBotsIterator()		{ return bots.begin();		}
	list<Bot*>::iterator	getEndOfBotsIterator()	{ return bots.end();		}
	GridPathfinder*			getPathfinder()			{ return pathfinder;		}

	// METHODS DEFINED IN SpriteManager.cpp
	void				addBot(Bot *botToAdd);
	void				addSpriteItemsToRenderList(Game *game);
	unsigned int		addSpriteType(AnimatedSpriteType *spriteTypeToAdd);
	void				addSpriteToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void				clearSprites();
	AnimatedSpriteType* getSpriteType(unsigned int typeIndex);
	Bot*				removeBot(Bot *botToRemove);
	void				setPathfinder(GridPathfinder *initPathfinder) { pathfinder = initPathfinder; }
	void				unloadSprites();
	void				update(Game *game);

	void resetBots(void);
	void makeRandomBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY); // MODIFIED: MAKE BOTS
};