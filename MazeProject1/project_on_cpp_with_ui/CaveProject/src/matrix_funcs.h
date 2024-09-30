#pragma once
#include "maze_gen_funcs.h"
#include <stdlib.h>
typedef enum TYPES {
    CELL_TYPE,
    INT_TYPE,
    MAZE_CELL_TYPE
}TYPES;
void** create_matrix(int height, int width, TYPES regime);
void free_matrix(void*** map, int height, TYPES);
void maze_path_print(maze_cell** map, int height, int width);