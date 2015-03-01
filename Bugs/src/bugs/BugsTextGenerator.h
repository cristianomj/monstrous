/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugsTextGenerator.h

	This class is a custom text generator for the EmptyGame
	application. Basically, by defining the initText and updateText
	methods, we can have it display whatever text we like.
*/

#pragma once
#include "bugs_VS\stdafx.h"
#include "sssf\text\TextGenerator.h"

class BugsTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring textToGenerate;
	wstring pathfindingText;

public:
	// NOTHING TO INITIALIZE OR DESTROY
	BugsTextGenerator()	{}
	~BugsTextGenerator()	{}

	// DEFINED IN BugsTextGenerator.cpp
	void appendMouseCoords(Game *game);
	void appendAntRotationInfo(Game *game);
	void appendPathfindingText(Game *game);
	void initText(Game *game);
	void updateText(Game *game);
};