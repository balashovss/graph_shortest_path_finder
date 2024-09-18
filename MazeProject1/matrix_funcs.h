#pragma once
#include "maze_gen_funcs.h"
#include <stdlib.h>
#define CELL_TYPE 0
#define INT_TYPE 1

void** create_matrix(int height, int width, int regime);
void free_matrix(void*** map, int height);
void maze_print(cell** map, int height, int width);