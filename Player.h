#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"
#include "Maze.h"
#include "AVLTree.h"
#include "Treasure.h"
#include "Enemy.h"


struct Point {
	int health;
	int swords;
	int enemies;
	int potions;
	int keys;
	int score;
};

class Player
{
public:
	CircleShape player;
	AVLTree inventory;
	Vec position;
	int health;
	Player(int radius, Vector2f Pos);
	Player() = default;
	void move(Cell ** maze, char key);
	int checkCollision(Treasure & treasure);
	bool checkCollision(Enemy * enemies, int numEnem);
	
};

#endif