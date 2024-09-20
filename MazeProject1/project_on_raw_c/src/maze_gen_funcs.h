#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ALIVE_PROBABILITY 70
#define SURVIVING 3
#define BIRTHING 3
#define NEEDED_NUMBER_OF_WALLS 0.5 * height * width
#define NEEDED_NUMBER_OF_WALLS_ON_GEN 0.7 * (*height) * (*width)
#define CAVE_GEN 0
#define MAZE_GEN 1
typedef enum cell{
    WALL,
    MOVABLE,
    PATH
}cell;
typedef struct maze_cell{
    unsigned char right;
    unsigned char bottom;
    int set;
}maze_cell;
int aliveness_counter(cell** map, int height, int width);
void fill_map(cell** map, int height, int width);
int aliveNeighbours(cell** map, int height, int width, int i, int j);
void check_aliveness(cell** map, cell** next_iteration_map_, int i, int j, int height, int width);
void next_iteration_map(cell** map, int height, int width);
void cellular_automata_cycle(cell** map, int height, int width);
cell** generate_maze(int* height, int* width, int type);
