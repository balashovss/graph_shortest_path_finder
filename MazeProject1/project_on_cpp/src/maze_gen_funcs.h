#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ALIVE_PROBABILITY 70
#define SURVIVING 2
#define BIRTHING 3
#define NEEDED_NUMBER_OF_WALLS 0.4 * height * width
#define NEEDED_NUMBER_OF_WALLS_ON_GEN 0.7 * height * width
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
    unsigned char isPartOfPath;
    int set;
}maze_cell;
int aliveness_counter(cell** map, int height, int width);
void fill_map(cell** map, int height, int width);
int aliveNeighbours(cell** map, int height, int width, int i, int j);
void check_aliveness(cell** map, cell** next_iteration_map_, int i, int j, int height, int width);
void next_iteration_map(cell** map, int height, int width);
void cellular_automata_cycle(cell** map, int height, int width);
void** generate_map(int* height, int* width, int type);
void generate_cave(void*** map, int height, int width);
void this_string_to_map(maze_cell* tmp, maze_cell** map, int index, int width);
void last_maze_string(maze_cell* tmp, int width, int* set_count);
void string_for_next_cycle(maze_cell* tmp, int width, int* set_count);
void all_maze_cells_to_one_set(maze_cell* tmp, int width, int j);
void string_bottom_wall_add(maze_cell* tmp, int width);
void string_right_wall_add(maze_cell* tmp, int width);
void string_init(int* set_count, int width, maze_cell* tmp);
void generate_maze(void*** map, int height, int width);
