#ifndef GAME_H
#define GAME_H

#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
#include "Treasure.h"
#include "AVLTree.h"



class Game {
public:
    Maze maze;
    Player runner;
    Enemy* enemies;
    Treasure treasure;
    Font f;
    Text* texts;
    Point points;
    Sprite bak;
    Texture bakT;
    short numEnem;
    Game();
    void genMaze();
    void Score();
    void drawScore(RenderWindow& window);
    void updateScore(bool check1, int check2);
    int start(RenderWindow& window);
    void Hint(Clock& clock, bool& hint, RenderWindow& window);
    void displayMaze(RenderWindow& window);
    void displayEnemy(RenderWindow& window);
    bool GameOver();
    bool GameWin();
    void GameOverMsg(RenderWindow& window);
    void GameWinMsg(RenderWindow& window);
    ~Game();
};



#endif
