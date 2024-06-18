#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    mainmenuSelection = 1;
    status = -1;
    if (!f.loadFromFile("font/cascadia.ttf")) {
        std::cerr << "Font loading failed!" << std::endl;
    }
    // Initializing menu items
    for (int i = 0; i < Max_main_menu; i++) {
        mainmenu[i].setFont(f);
        mainmenu[i].setFillColor(Color::White);
    }
    mainmenu[0].setCharacterSize(60);
    mainmenu[0].setPosition((MAZE_WIDTH * CELL_SIZE ) / 2, 60 + 0 * 100);
    mainmenu[1].setCharacterSize(30);
    mainmenu[1].setPosition(((MAZE_WIDTH * CELL_SIZE + 200) - 100) / 2, 100 + 1 * 100);
    mainmenu[2].setCharacterSize(30);
    mainmenu[2].setPosition(((MAZE_WIDTH * CELL_SIZE + 200) - 30) / 2, 70 + 2 * 100);
    mainmenu[3].setCharacterSize(30);
    mainmenu[3].setPosition(((MAZE_WIDTH * CELL_SIZE + 200) - 30) / 2, 40+ 3 * 100);
    
    mainmenu[0].setFillColor(Color::Red);
    mainmenu[mainmenuSelection].setFillColor(Color::Blue);

    mainmenu[0].setString("Labyrinth");
    mainmenu[1].setString("New Game");
    mainmenu[2].setString("Help");
    mainmenu[3].setString("Exit");
    
}

void Menu::draw(RenderWindow& window) {
    if (status == 0)
        mainmenu[1].setString("Continue");
    for (int i = 0; i < Max_main_menu; i++) {
        window.draw(mainmenu[i]);
    }
}

void Menu::moveup() {
    if (mainmenuSelection - 1 >= 0) {
        mainmenu[mainmenuSelection].setFillColor(Color::White);
        mainmenuSelection--;
        if (mainmenuSelection == 0) {
            mainmenuSelection = 3;
        }
        mainmenu[mainmenuSelection].setFillColor(Color::Blue);
    }
    if (mainmenuSelection == 0)
        mainmenuSelection = 1;
}

void Menu::movedown() {
    if (mainmenuSelection + 1 <= 4) {
        mainmenu[mainmenuSelection].setFillColor(Color::White);
        mainmenuSelection++;
        if (mainmenuSelection == 4) {
            mainmenuSelection = 1;
        }
        mainmenu[mainmenuSelection].setFillColor(Color::Blue);
    }
}

int Menu::mainmenuButton() {
    return mainmenuSelection;
}

void Menu::Help(RenderWindow & HELP) {
    
    RectangleShape instructions;
    instructions.setSize(Vector2f(HELP.getSize()));
    Texture Maintexture2;
    Maintexture2.loadFromFile("img/bak_help.jpg");
    instructions.setTexture(&Maintexture2);
    bool close = false;
    music.openFromFile("audio/game.ogg");
    music.play();
    while (HELP.isOpen())
    {
        Event aevent;
        while (HELP.pollEvent(aevent))
        {
            if (aevent.type == Event::Closed)
            {
                HELP.close();
            }
            if (aevent.type == Event::KeyPressed)
            {
                if (aevent.key.code == Keyboard::Escape)
                {
                    close = true;
                    break;
                }
            }
        }
        if (close)
            break;

        HELP.clear();
        HELP.draw(instructions);
        HELP.display();
    }

}

void Menu::updateStatus(int & status) {
    if (status == 1 || status == 2) {
        game.maze.generateMaze();
        game.runner.player.setPosition(Vector2f(0, 0));
        game.points.enemies = 10;
        game.points.health = 100;
        game.runner.health = 100;
        game.points.keys  = 0;
        game.points.potions = 0;
        game.points.swords = 0;
        game.runner.inventory.deleteTree(game.runner.inventory.root);
        game.treasure.randomTreasure();
        game.maze.dijkstra(game.maze.maze, 0, 0);
        status = 0;
    }
}

void Menu::display_menu() {
    
    RenderWindow MENU(sf::VideoMode(MAZE_WIDTH * CELL_SIZE + 200 , MAZE_HEIGHT * CELL_SIZE), "Lybrinth Explorer");
    Menu mainmenu(MENU.getSize().x, MENU.getSize().y);

    Sprite background;
    Texture Maintexture;
    Maintexture.loadFromFile("img/bak_menu.jpeg");
    background.setTexture(Maintexture);
    game.genMaze();
    game.treasure.randomTreasure();
    while (MENU.isOpen())
    {
        Event event;
        while (MENU.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                MENU.close();
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    mainmenu.moveup();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    mainmenu.movedown();
                    break;
                }
                if (event.key.code == Keyboard::Return)
                {
                    int x = mainmenu.mainmenuButton();
                    if (x == 1)
                    {
                        status = game.start(MENU);
                        updateStatus(status);
                    }
                  
                    else if (x == 2)
                    {
                        Help(MENU);
                    }

                    else if (x == 3)
                    {
                        MENU.close();
                    }
                }
            }
        }
        MENU.clear();
        MENU.draw(background);
        mainmenu.draw(MENU);
        MENU.display();
    }
}