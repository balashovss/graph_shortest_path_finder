#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ALIVE_PROBABILITY 70
#define SURVIVING 1
#define BIRTHING 3
#define NEEDED_NUMBER_OF_WALLS 0.4 * height * width
#define NEEDED_NUMBER_OF_WALLS_ON_GEN 0.7 * (*height) * (*width)
typedef enum cell{
    WALL,
    MOVABLE
}cell;

int aliveness_counter(cell** map, int height, int width);
void fill_map(cell** map, int height, int width);
int aliveNeighbours(cell** map, int height, int width, int i, int j);
void check_aliveness(cell** map, cell** next_iteration_map_, int i, int j, int height, int width);
void next_iteration_map(cell** map, int height, int width);
void cellular_automata_cycle(cell** map, int height, int width);
cell** generate_maze(int* height, int* width);
