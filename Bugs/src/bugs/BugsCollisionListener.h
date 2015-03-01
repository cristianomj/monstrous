#pragma once

#include "bugs_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\physics\CollisionListener.h"
#include "sssf\gsm\physics\Collision.h"

class BugsCollisionListener : public CollisionListener
{
public:
	void respondToCollision(Game *game, Collision *collision);
};