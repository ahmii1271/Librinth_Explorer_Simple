#ifndef TREASURE_H
#define TREASURE_H

#include "Utils.h"
#include "Maze.h"

class Treasure
{
public:
	Sprite *swords;
	Sprite *potions;
	Sprite *keys;
	Texture texS;
	Texture texP;
	Texture texK;
	int numS, numP, numK;
	Treasure();
	void randomTreasure();
	void displayTreasure(RenderWindow& window);
};

#endif 



