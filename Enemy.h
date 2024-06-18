#ifndef ENEMY_H
#define ENEMY_H

#include "Utils.h"
#include "Maze.h"
class Enemy
{
public:
	Sprite enemy;
	Texture tex;
	int health;
	Vec pos;
	Enemy();

};


#endif 

