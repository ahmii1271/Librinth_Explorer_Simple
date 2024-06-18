#include "Player.h"

Player::Player(int radius,Vector2f Pos) {
	player.setRadius(radius);
	player.setPosition(Pos);
	player.setFillColor(Color::Green);
    position.x = Pos.x;
    position.y = Pos.y;
    health = 100;
}


void Player::move(Cell** maze, char key) {
    Vector2f currentPosition = player.getPosition();

    int cellX = static_cast<int>(currentPosition.x / CELL_SIZE);
    int cellY = static_cast<int>(currentPosition.y / CELL_SIZE);
    if (cellX >= 0 && cellX < MAZE_WIDTH && cellY >= 0 && cellY < MAZE_HEIGHT) {
        if (key == 'w' && cellY-1 >= 0 && !maze[cellX][cellY-1].bottom_wall) {
            player.move(0, -CELL_SIZE);
        }
        else if (key == 's' && cellY+1 < MAZE_HEIGHT && !maze[cellX][cellY+1].top_wall ) {
            player.move(0, CELL_SIZE);
        }
        else if (key == 'a' && cellX -1 >= 0 && !maze[cellX-1][cellY].right_wall) {
            player.move(-CELL_SIZE, 0);
        }
        else if (key == 'd' && cellX+1 < MAZE_WIDTH && !maze[cellX+1][cellY].left_wall) {
            player.move(CELL_SIZE, 0);
        }
    }
    position.x = player.getPosition().x /CELL_SIZE;
    position.y = player.getPosition().y / CELL_SIZE;
}

int Player::checkCollision(Treasure & treasure) {
    int retVal = 0;
    for (int i = 0; i < treasure.numS; i++) {
        if (treasure.swords[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
            inventory.insert(1);
            treasure.swords[i].setPosition(Vector2f( - 100, -100));
            retVal = 1;
        }
    }
    for (int i = 0; i < treasure.numP; i++) {
        if (treasure.potions[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
            inventory.insert(2);
            treasure.potions[i].setPosition(Vector2f(-100, -100));
            retVal = 2;
        }
    }
    for (int i = 0; i < treasure.numK; i++) {
        if (treasure.keys[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
            inventory.insert(3);
            treasure.keys[i].setPosition(Vector2f(-100, -100));
            retVal = 3;
        }
    }
    return retVal;
}

bool Player::checkCollision(Enemy* enemies, int numEnem) {
    for (int i = 0; i < numEnem; i++) {
        if (enemies[i].enemy.getGlobalBounds().intersects(player.getGlobalBounds())) {
            enemies[i].enemy.setPosition(Vector2f(-100, -100));
            return true;
        }
    }
    return false;
}