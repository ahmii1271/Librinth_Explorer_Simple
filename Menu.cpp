#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) : window(sf::VideoMode(width, height), "Main Menu", sf::Style::Default) {
    mainmenuSelection = -1;
    if (!f.loadFromFile("font/cascadia.ttf")) {
        std::cerr << "Font loading failed!" << std::endl;
    }

    // Initialize menu items
    for (int i = 0; i < Max_main_menu; i++) {
        mainmenu[i].setFont(f);
        mainmenu[i].setFillColor(sf::Color::White);
        mainmenu[i].setCharacterSize(70);
        mainmenu[i].setPosition(400, 200 + i * 100);
    }

    mainmenu[0].setString("Start Game");
    mainmenu[1].setString("HighScore");
    mainmenu[2].setString("Help");
    mainmenu[3].setString("Exit");
    mainmenu[4].setString("Explorer");
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < Max_main_menu; i++) {
        window.draw(mainmenu[i]);
    }
}

void Menu::moveup() {
    if (mainmenuSelection - 1 >= -1) {
        mainmenu[mainmenuSelection].setFillColor(sf::Color::White);
        mainmenuSelection--;
        if (mainmenuSelection == -1) {
            mainmenuSelection = 3;
        }
        mainmenu[mainmenuSelection].setFillColor(sf::Color::Blue);
    }
}

void Menu::movedown() {
    if (mainmenuSelection + 1 <= 4) {
        mainmenu[mainmenuSelection].setFillColor(sf::Color::White);
        mainmenuSelection++;
        if (mainmenuSelection == 4) {
            mainmenuSelection = 0;
        }
        mainmenu[mainmenuSelection].setFillColor(sf::Color::Blue);
    }
}

int Menu::mainmenuButton() {
    return mainmenuSelection;
}

void Menu::display_menu() {
    RenderWindow MENU(VideoMode(800, 600), "Main Menu", Style::Default);
	Menu mainmenu(MENU.getSize().x, MENU.getSize().y);

    //// setting background
    RectangleShape background;
    background.setSize(Vector2f(800, 600));
    Texture Maintexture;
    Maintexture.loadFromFile("img/bak_menu.jpg");
    background.setTexture(&Maintexture);

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
                    if (x == 0)
                    {
                        // Handle Start Game option
                        std::cout << "Game start\n";
                        //  g.start_game();
                    }
                    else if (x == 1)
                    {
                        // Handle HighScore option
                        // ...

                        RenderWindow  HIGHSCORE(VideoMode(800, 600), "HighScore");
                        Font font;
                        font.loadFromFile("bahnschrift.ttf");

                        Text highScoresText;
                        highScoresText.setFont(font);
                        highScoresText.setCharacterSize(30);
                        highScoresText.setFillColor(Color::Red);
                        highScoresText.setPosition(10, 10);

                        /* std::ifstream file()
                         std::string scoresText;
                         if (file.is_open())
                         {
                             std::string line;
                             scoresText += "High Scores:\n";
                             while (getline(file, line))
                             {
                                 scoresText += line + "\n";
                             }
                             file.close();
                         }


                         highScoresText.setString(scoresText);*/


                        while (HIGHSCORE.isOpen())
                        {
                            Event aevent;
                            while (HIGHSCORE.pollEvent(aevent))
                            {
                                if (aevent.type == Event::Closed)
                                {
                                    HIGHSCORE.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        HIGHSCORE.close();
                                    }
                                }

                            }
                            HIGHSCORE.clear(Color::Black);
                            HIGHSCORE.draw(highScoresText);
                            HIGHSCORE.display();
                        }
                        /* HIGHSCORE.clear(Color::Black);
                         HIGHSCORE.draw(highScoresText);
                         HIGHSCORE.display();*/

                    }
                    else if (x == 2)
                    {

                        // Handle Help option
                        RenderWindow HELP(VideoMode(1000, 900), "Help");

                        RectangleShape instructions;
                        instructions.setSize(Vector2f(1200, 900));
                        Texture Maintexture2;
                        Maintexture2.loadFromFile("img/instructions.png");
                        instructions.setTexture(&Maintexture2);

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
                                        HELP.close();
                                    }
                                }
                            }

                            HELP.clear();
                            HELP.draw(instructions);
                            HELP.display();
                        }


                    }

                    else if (x == 3)
                    {
                        // Handle Exit option
                        MENU.close();
                    }
                }
            }
        }

        // Clear, draw, and display
        MENU.clear();
        MENU.draw(background);
        mainmenu.draw(MENU);
        MENU.display();
    }
}