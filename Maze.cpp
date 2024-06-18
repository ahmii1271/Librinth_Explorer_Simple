#include "Maze.h"

Maze::Maze() {
    maze = nullptr;
    mazeT.loadFromFile("img/bak_maze.jpg");
    mazeS.setTexture(mazeT);
}

bool Maze::isValid(int x, int y) {
    return x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT;
}

void Maze::addWalls(int** walls, int& wall_count, int x, int y, bool** in_maze) {
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny) && !in_maze[nx][ny]) {
            walls[wall_count][0] = x;
            walls[wall_count][1] = y;
            walls[wall_count][2] = i; 
            wall_count++;
        }
    }
}

void Maze::removeWall(Cell** maze, int x, int y, int direction) {
    if (direction == 0) { 
        maze[x][y].top_wall = false;
        if (y > 0) maze[x][y - 1].bottom_wall = false;
    }
    else if (direction == 1) { 
        maze[x][y].bottom_wall = false;
        if (y < MAZE_HEIGHT - 1) maze[x][y + 1].top_wall = false;
    }
    else if (direction == 2) { 
        maze[x][y].left_wall = false;
        if (x > 0) maze[x - 1][y].right_wall = false;
    }
    else if (direction == 3) { 
        maze[x][y].right_wall = false;
        if (x < MAZE_WIDTH - 1) maze[x + 1][y].left_wall = false;
    }
}

void Maze::drawMaze(RenderWindow& window) {
    for (int i = 0; i < MAZE_WIDTH; ++i) {
        for (int j = 0; j < MAZE_HEIGHT; ++j) {
            float x = i * CELL_SIZE;
            float y = j * CELL_SIZE;

            if (maze[i][j].top_wall) {
                RectangleShape top(Vector2f(CELL_SIZE, 1));
                top.setFillColor(Color::White);
                top.setPosition(x, y);
                window.draw(top);
            }
            if (maze[i][j].bottom_wall) {
                RectangleShape bottom(Vector2f(CELL_SIZE, 1));
                bottom.setFillColor(Color::White);
                bottom.setPosition(x, y + CELL_SIZE);
                window.draw(bottom);
            }
            if (maze[i][j].left_wall) {
                RectangleShape left(Vector2f(1, CELL_SIZE));
                left.setFillColor(Color::White);
                left.setPosition(x, y);
                window.draw(left);
            }
            if (maze[i][j].right_wall) {
                RectangleShape right(Vector2f(1, CELL_SIZE));
                right.setFillColor(Color::White);
                right.setPosition(x + CELL_SIZE, y);
                window.draw(right);
            }
        }
    }
}

void Maze::dijkstra(Cell** maze, int start_x, int start_y) {
    priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq;
    pq.push({ 0, {start_x, start_y} });
    maze[start_x][start_y].distance = 0;

    while (!pq.empty()) {
        int curr_x = pq.top().second.first;
        int curr_y = pq.top().second.second;
        pq.pop();

        if (maze[curr_x][curr_y].visited)
            continue;

        maze[curr_x][curr_y].visited = true;

        for (int i = 0; i < 4; ++i) {
            int nx = curr_x + dx[i];
            int ny = curr_y + dy[i];

            if (isValid(nx, ny) && !maze[nx][ny].visited && !isWall(curr_x, curr_y, i) && maze[nx][ny].distance > maze[curr_x][curr_y].distance + 1) {
                maze[nx][ny].distance = maze[curr_x][curr_y].distance + 1;
                maze[nx][ny].parent_x = curr_x;
                maze[nx][ny].parent_y = curr_y;
                pq.push({ maze[nx][ny].distance, {nx, ny} });
            }
        }
    }
}

bool Maze::isWall(int x, int y, int direction) {
    if (direction == 0) // Top wall
        return maze[x][y].top_wall;
    else if (direction == 1) // Bottom wall
        return maze[x][y].bottom_wall;
    else if (direction == 2) // Left wall
        return maze[x][y].left_wall;
    else if (direction == 3) // Right wall
        return maze[x][y].right_wall;
    return false;
}

void Maze::drawPath(RenderWindow& window, Cell** maze, int end_x, int end_y) {
    int curr_x = end_x;
    int curr_y = end_y;

    while (maze[curr_x][curr_y].parent_x != -1 && maze[curr_x][curr_y].parent_y != -1) {
        int parent_x = maze[curr_x][curr_y].parent_x;
        int parent_y = maze[curr_x][curr_y].parent_y;

        int dx = parent_x - curr_x;
        int dy = parent_y - curr_y;

        if (dx == 1 && dy == 0) // Move right
            drawLine(window, curr_x, curr_y, 3);
        else if (dx == -1 && dy == 0) // Move left
            drawLine(window, curr_x, curr_y, 2);
        else if (dx == 0 && dy == 1) // Move down
            drawLine(window, curr_x, curr_y, 1);
        else if (dx == 0 && dy == -1) // Move up
            drawLine(window, curr_x, curr_y, 0);

        curr_x = parent_x;
        curr_y = parent_y;
    }
}

void Maze::drawLine(RenderWindow& window, int x, int y, int direction) {
    float startX = x * CELL_SIZE + CELL_SIZE / 2;
    float startY = y * CELL_SIZE + CELL_SIZE / 2;
    float endX = startX;
    float endY = startY;

    if (direction == 0)
        endY -= CELL_SIZE / 2;
    else if (direction == 1)
        endY += CELL_SIZE / 2;
    else if (direction == 2)
        endX -= CELL_SIZE / 2;
    else if (direction == 3)
        endX += CELL_SIZE / 2;

    Vertex line[] =
    {
        Vertex(Vector2f(startX, startY)),
        Vertex(Vector2f(endX, endY))
    };
    line->color = Color::Black;

    window.draw(line, 2, Lines);
}

void Maze::generateMaze() {
    srand(time(0));
    maze = new Cell * [MAZE_WIDTH];
    for (int i = 0; i < MAZE_WIDTH; ++i) {
        maze[i] = new Cell[MAZE_HEIGHT];
    }

    int wall_count = 0;
    int** walls = new int* [MAX_WALLS];
    for (int i = 0; i < MAX_WALLS - 1; i++)
        walls[i] = new int[3];

    bool** in_maze = new bool* [MAZE_WIDTH];
    for (int i = 0; i < MAZE_WIDTH; i++) {
        in_maze[i] = new bool[MAZE_HEIGHT];
        for (int j = 0; j < MAZE_HEIGHT; j++)
            in_maze[i][j] = false;
    }
    int start_x = rand() % MAZE_WIDTH;
    int start_y = rand() % MAZE_HEIGHT;
    in_maze[start_x][start_y] = true;

    addWalls(walls, wall_count, start_x, start_y, in_maze);

    while (wall_count > 0) {
        int random_index = rand() % wall_count;
        int x = walls[random_index][0];
        int y = walls[random_index][1];
        int direction = walls[random_index][2];

        int opposite_x = x + dx[direction];
        int opposite_y = y + dy[direction];

        if (isValid(opposite_x, opposite_y) && !in_maze[opposite_x][opposite_y]) {
            removeWall(maze, x, y, direction);
            in_maze[opposite_x][opposite_y] = true;

            addWalls(walls, wall_count, opposite_x, opposite_y, in_maze);
        }

        walls[random_index][0] = walls[wall_count - 1][0];
        walls[random_index][1] = walls[wall_count - 1][1];
        walls[random_index][2] = walls[wall_count - 1][2];
        wall_count--;
    }
    maze[0][0].left_wall = 0;
    maze[MAZE_WIDTH - 1][MAZE_HEIGHT - 1].right_wall = 0;
    maze[MAZE_WIDTH - 1][MAZE_HEIGHT - 1].left_wall = 0;
    maze[MAZE_WIDTH - 1][MAZE_HEIGHT - 1].top_wall = 0;
}