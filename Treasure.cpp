#include "Treasure.h"

Treasure::Treasure() {
	numS = 3;
	numP = 2;
	numK = 2;
	swords = new Sprite[numS];
	potions = new Sprite[numP];
	keys = new Sprite[numK];
	texS.loadFromFile("img/sword.png");
	texP.loadFromFile("img/potion.png");
	texK.loadFromFile("img/key.png");
	for (int i = 0; i < numS; i++) {
		swords[i].setTexture(texS);
	}
	for (int i = 0; i < numP; i++)
	{
		potions[i].setTexture(texP);
	}
	for (int i = 0; i < numK; i++)
	{
		keys[i].setTexture(texK);
	}
}

void Treasure::randomTreasure() {
	for (int i = 0; i < numS; i++)
		swords[i].setPosition(Vector2f(rand() % MAZE_WIDTH * CELL_SIZE, rand() % MAZE_HEIGHT * CELL_SIZE));
	for (int i = 0; i < numP; i++)
		potions[i].setPosition(Vector2f(rand() % MAZE_WIDTH * CELL_SIZE, rand() % MAZE_HEIGHT * CELL_SIZE));
	for (int i = 0; i < numK; i++)
		keys[i].setPosition(Vector2f(rand() % MAZE_WIDTH * CELL_SIZE, rand() % MAZE_HEIGHT * CELL_SIZE));
}

void Treasure::displayTreasure(RenderWindow & window) {
	for (int i = 0; i < numS; i++)
		window.draw(swords[i]);
	for (int i = 0; i < numP; i++)
		window.draw(potions[i]);
	for (int i = 0; i < numK; i++)
		window.draw(keys[i]);
}