#include "Menu.h"

int main()
{
    Menu menu(MAZE_WIDTH * CELL_SIZE + 200, MAZE_HEIGHT * CELL_SIZE);
    menu.display_menu();
    return 0;
}