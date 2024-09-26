#pragma once
#include "path_planning_algs.h"
#include "maze_gen_funcs.h"
int** wave_map_init(int height, int width);
void wave_map_step_for_cave(int** wave_map, cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter);
int wave_map_filling_for_cave(int** wave_map, cell** map, int height, int width);
void wave_algorithm_for_cave(cell*** map, int height, int width);
void wave_algorithm_for_maze(maze_cell*** map, int height, int width);
void wave_map_step_for_cave(int** wave_map, cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter);
int wave_map_filling_for_maze(int** wave_map, maze_cell** map, int height, int width);
void wave_map_step_for_maze(int** wave_map, maze_cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter);