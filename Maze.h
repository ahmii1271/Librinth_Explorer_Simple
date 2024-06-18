#ifndef MAZE_H
#define MAZE_H

#include "Utils.h"

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

struct Cell {
    bool top_wall = true;
    bool bottom_wall = true;
    bool left_wall = true;
    bool right_wall = true;
    int distance = INF;
    bool visited = false;
    int parent_x = -1;
    int parent_y = -1;
};

class Maze {
public:
    Cell** maze;
    Sprite mazeS;
    Texture mazeT;
    Maze();
    bool isValid(int x, int y);
    void addWalls(int** walls, int& wall_count, int x, int y, bool** in_maze);
    void drawLine(RenderWindow& window, int x, int y, int direction);
    bool isWall(int x, int y, int direction);
    void removeWall(Cell** maze, int x, int y, int direction);
    void drawMaze(RenderWindow& window);
    void drawPath(RenderWindow& window, Cell** maze, int end_x, int end_y);
    void dijkstra(Cell** maze, int start_x, int start_y);
    void generateMaze();
};
#endif // !MAZE_H