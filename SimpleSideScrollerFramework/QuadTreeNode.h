#pragma once

#include <vector>
#include <unordered_set>
#include "sssf\gsm\ai\Bot.h"

const unsigned int maximumOccupants = 6;
const unsigned int minimumOccupants = 1;
const unsigned int maxLevels = 3;

class QuadTree;

class QuadTreeNode
{
public:
	QuadTreeNode();
	~QuadTreeNode();
};

