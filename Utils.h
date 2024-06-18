#ifndef UTILS_H
#define UTILS_H

extern float CELL_SIZE;
extern int MAZE_WIDTH;
extern int MAZE_HEIGHT;
extern int MAX_WALLS;
extern const int INF;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;
using namespace sf;

struct Vec {
	int x;
	int y;
};

#endif 

