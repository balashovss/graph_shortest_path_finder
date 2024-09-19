#pragma once
#include "path_planning_algs.h"
#include "maze_gen_funcs.h"
void print_waves(int** wave_map, int height, int width);
int** wave_map_init(int height, int width);
void wave_map_step(int** wave_map, cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter);
void wave_map_filling(int** wave_map, cell** map, int height, int width);
void wave_algorithm(cell*** map, int height, int width);