#ifndef MENU_H
#define MENU_H

#include "Game.h"
#define Max_main_menu 4

class Menu {
public:
    Game game;
    Music music;
    int mainmenuSelection;
    Font f;
    Text mainmenu[Max_main_menu];
    int status; // 0 normal(continue), 1 gameLose(newGame), 2 gameWin(newGame) 
    Menu(float width, float height);
    void draw(RenderWindow& window);
    void Help(RenderWindow& HELP);
    void moveup();
    void movedown();
    int mainmenuButton();
    void updateStatus(int& status);
    void display_menu();
};

#endif // MENU_H