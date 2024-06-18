#include "Enemy.h"

Enemy::Enemy() {
	tex.loadFromFile("img/enemy.png");
	enemy.setTexture(tex);
	health = rand() % 25 + 10;;
}
