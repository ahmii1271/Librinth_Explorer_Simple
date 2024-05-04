#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
using namespace sf;
#define Max_main_menu 5

class Menu {
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveup();
    void movedown();
    int mainmenuButton();
    void display_menu();

private:
    sf::RenderWindow window;
    int mainmenuSelection;
    sf::Font f;
    sf::Text mainmenu[Max_main_menu];
};

#endif // MENU_H
