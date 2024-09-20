#pragma once
#include "maze_gen_funcs.h"
#include <stdlib.h>
#define CELL_TYPE 0
#define INT_TYPE 1
#define MAZE_CELL_TYPE 2
void** create_matrix(int height, int width, int regime);
void free_matrix(void*** map, int height);
void cave_print(cell** map, int height, int width);
void maze_print(maze_cell** map, int height, int width);