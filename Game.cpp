#include "Game.h"

Game::Game() {
    runner = Player(CELL_SIZE / 2 - 1, Vector2f(0, 0));
    numEnem = 10;
    enemies = new Enemy[numEnem];
    for (int i = 0; i < numEnem; i++) {
        enemies[i].enemy.setPosition(Vector2f(rand() % MAZE_WIDTH * CELL_SIZE, rand() % MAZE_HEIGHT * CELL_SIZE));
        enemies[i].pos.x = enemies[i].enemy.getPosition().x;
        enemies[i].pos.y = enemies[i].enemy.getPosition().y;
    }
    bakT.loadFromFile("img/bak_inventory.jpg");
    bak.setTexture(bakT);
    bak.setPosition(MAZE_WIDTH * CELL_SIZE, 0);
}

void Game::displayEnemy(RenderWindow& window) {
    for (short i = 0; i < numEnem; i++)
        window.draw(enemies[i].enemy);
}

void Game::Hint(Clock& clock, bool& hint, RenderWindow& window) {
    if (hint && clock.getElapsedTime().asSeconds() < 2) {
        maze.dijkstra(maze.maze, MAZE_WIDTH - 1, MAZE_HEIGHT - 1);
        maze.drawPath(window, maze.maze, MAZE_WIDTH - 1, MAZE_HEIGHT - 1);
    }
    else {
        hint = false;
    }
}

int Game::start(RenderWindow& window) {
    bool close = false;
    Clock clock;
    bool hint = false;
    bool check1 = false;
    int check2 = 0;
    int retVal = 0; // if 0 gamePause, if 1 gameOver, if 2 gameWin
    Score();
    while (window.isOpen())
    {
        window.clear(Color::White);
        window.draw(bak);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                break;
                close = true;
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    close = true;
                    break;
                }
                if (event.key.code == Keyboard::W) {
                    runner.move(maze.maze, 'w');
                    check1 = runner.checkCollision(enemies, numEnem);
                    check2 = runner.checkCollision(treasure);
                    updateScore(check1, check2);
                }
                if (event.key.code == Keyboard::A) {
                    runner.move(maze.maze, 'a');
                    check1 = runner.checkCollision(enemies, numEnem);
                    check2 = runner.checkCollision(treasure);
                    updateScore(check1, check2);
                }
                if (event.key.code == Keyboard::S) {
                    runner.move(maze.maze, 's');
                    check1 = runner.checkCollision(enemies, numEnem);
                    check2 = runner.checkCollision(treasure);
                    updateScore(check1, check2);
                }
                if (event.key.code == Keyboard::D) {
                    runner.move(maze.maze, 'd');
                    check1 = runner.checkCollision(enemies, numEnem);
                    check2 = runner.checkCollision(treasure);
                    updateScore(check1, check2);
                }
                if (event.key.code == Keyboard::H && points.keys > 0) {
                    hint = true;
                    points.keys--;
                    clock.restart();
                }
                if (event.key.code == Keyboard::P && points.potions > 0) {
                    if (runner.health < 80) {
                        runner.health += 20; points.health += 20;
                    }
                }
            }
        }
        if (close) {
            retVal = 0;
            break;
        }
        if (GameOver()) {
            retVal = 1;
            GameOverMsg(window);
            break;
        }
        if (GameWin()) {
            retVal = 2;
            GameWinMsg(window);
            break;
        }
        drawScore(window);
        window.draw(maze.mazeS);
        displayMaze(window);
        maze.dijkstra(maze.maze, runner.position.x, runner.position.y);
        maze.drawPath(window, maze.maze, runner.position.x, runner.position.y);
        displayEnemy(window);
        treasure.displayTreasure(window);
        window.draw(runner.player);
        Hint(clock, hint, window);
        window.display();
    }
    return retVal;
}

void Game::genMaze() {
    maze.generateMaze();
}

void Game::displayMaze(RenderWindow& window) {
    maze.drawMaze(window);
}

void Game::Score() {
    f.loadFromFile("font/cascadia.ttf");
    texts = new Text[6];
    for (int i = 0; i < 6; i++) {
        texts[i].setFont(f);
        texts[i].setFillColor(Color::Black);
        texts[i].setCharacterSize(15);
    }
    texts[0].setCharacterSize(20);

    points.enemies = numEnem;
    points.keys = treasure.numK;
    points.health = runner.health;
    points.swords = runner.inventory.findFrequency(1);
    points.potions = runner.inventory.findFrequency(2);
    points.keys = runner.inventory.findFrequency(3);

    texts[0].setString("Inventory");
    texts[1].setString("Health: "+to_string(points.health));
    texts[2].setString("Swords: "+to_string(points.swords));
    texts[3].setString("Potions: "+to_string(points.potions));
    texts[4].setString("Keys: " + to_string(points.keys));
    texts[5].setString("Enemies: "+to_string(points.enemies));

    
    texts[0].setPosition(MAZE_WIDTH * CELL_SIZE + 50,80);
    texts[1].setPosition(MAZE_WIDTH * CELL_SIZE + 55, 120);
    texts[2].setPosition(MAZE_WIDTH * CELL_SIZE + 55, 150);
    texts[3].setPosition(MAZE_WIDTH * CELL_SIZE + 55, 180);
    texts[4].setPosition(MAZE_WIDTH * CELL_SIZE + 55, 210);
    texts[5].setPosition(MAZE_WIDTH * CELL_SIZE + 55, 240);

}

void Game::drawScore(RenderWindow& window) {
    texts[1].setString("Health: " + to_string(points.health));
    texts[2].setString("Swords: " + to_string(points.swords));
    texts[3].setString("Potions: " + to_string(points.potions));
    texts[4].setString("Keys: " + to_string(points.keys));
    texts[5].setString("Enemies: " + to_string(points.enemies));
    for (int i = 0; i < 6; i++)
        window.draw(texts[i]);
}

void Game::updateScore(bool check1,int check2) {
    if (check1) {
        points.enemies--;
        if (points.swords <= 0){
            runner.health -= 25;
            points.health -= 25;
        }
        else {
            points.swords--;
        }
    }
    switch (check2)
    {
    case 0:
        break;
    case 1:
        points.swords++;
        break;
    case 2:
        points.potions++;
        break;
    case 3:
        points.keys++;
        break;
    default:
        break;
    }
}

bool Game::GameOver() {
    return runner.health <= 0;
}

bool Game::GameWin() {
    if (runner.position.x == MAZE_WIDTH - 1 && runner.position.y == MAZE_HEIGHT - 1)
        return true;
    return false;
}

void Game::GameOverMsg(RenderWindow& window) {
    Font font;
    font.loadFromFile("font/cascadia.ttf");
    Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
        window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);

    while (window.isOpen()) {
        bool close = false;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Return) {
                    close = true; break;
                }
        }
        if (close) break;
        window.clear();
        window.draw(gameOverText);
        window.display();
    }
}

void Game::GameWinMsg(RenderWindow& window) {
    Font font;
    font.loadFromFile("font/cascadia.ttf");

    Text gameWinText("You Escaped", font, 50);
    gameWinText.setFillColor(Color::Green);
    gameWinText.setStyle(Text::Bold);
    gameWinText.setPosition(window.getSize().x / 2 - gameWinText.getGlobalBounds().width / 2,
        window.getSize().y / 2 - gameWinText.getGlobalBounds().height / 2);

    while (window.isOpen()) {
        Event event;
        bool close = false;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Return) {
                    close = true; break;
                }
        }
        if (close)
            break;
        window.clear();
        window.draw(gameWinText);
        window.display();
    }
}

Game::~Game() {}


