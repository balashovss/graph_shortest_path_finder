#include <stdio.h>
#include <stdlib.h>
#include "path_planning_algs.h"
#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
void print_waves(int** wave_map, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", wave_map[i][j]);
        }
        printf("\n");
    }
}
int** wave_map_init(int height, int width) {
    int** wave_map = (int**)create_matrix(height, width, INT_TYPE);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            wave_map[i][j] = -1;
        }
    }
    wave_map[0][0] = 0;
    return wave_map;
}
int wave_map_filling_for_cave(int** wave_map, cell** map, int height, int width) {
    int wave_counter = 0, wave_spreading_counter = 1,flag = 0;
    while ((wave_spreading_counter != 0) && !flag) {
        wave_spreading_counter = 0;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++) {
                wave_map_step_for_cave(wave_map,map,height,width,i,j, wave_counter,&flag,&wave_spreading_counter);
            }
        }
        wave_counter++;
    }
    if (!flag) printf("Путь не найден!\n");
    return flag;
}
void wave_algorithm_for_cave(cell*** map, int height, int width){
    if (*map != NULL) {
        int** wave_map = wave_map_init(height, width);
        if (wave_map_filling_for_cave(wave_map, *map, height, width)) {
        print_waves(wave_map, height, width);
        int* stack = (int*)malloc(sizeof(int)*height*width);
        int top = 0;
        stack[top] = -1;
        int i = height - 1, j = width - 1;
        while (wave_map[i][j] != 0) {
            top++;
            stack[top] = i*height+j;
            int flag = 0;
            for (int k = -1; ((k < 2) && (!flag)); k++) {
                for (int l = -1; ((l < 2) && (!flag)); l++) {
                    if ((i+k < 0) || (i+k >= height) || (j+l < 0) || (j+l >= width) || ((l == 0) && (k == 0)) || (wave_map[i+k][j+l] == -1) || (wave_map[i+k][j+l] == wave_map[height - 1][width - 1])) continue;
                    if (wave_map[i+k][j+l] == wave_map[i][j] - 1) {
                        if ((i != height - 1) && (j != width - 1)) wave_map[i][j] = -1;
                        i = i+k;
                        j = j+l;
                        flag = 1;
                    }
                }
            }
            if (!flag) {
            while (stack[top] != -1) top--;
                i = height - 1;
                j = width - 1;
            }
        }
        while ((stack[top] != -1) && (top >= 0)) {
            if (width >= height)(*map)[stack[top]/width][stack[top]%width] = PATH;
            else (*map)[stack[top]/height][stack[top]%height] = PATH;
            top--;
        }
        (*map)[0][0] = PATH;
        cave_print(*map, height, width);
        free(stack);
        }
        free_matrix((void***)map, height);
        free_matrix((void***)(&wave_map), height);
    }
}
void wave_algorithm_for_maze(maze_cell*** map, int height, int width){
    if (*map != NULL) {
        int** wave_map = wave_map_init(height, width);
        if (wave_map_filling_for_maze(wave_map, *map, height, width)) {
        print_waves(wave_map, height, width);
        int* stack = (int*)malloc(sizeof(int)*height*width);
        int top = 0;
        stack[top] = -1;
        int i = height - 1, j = width - 1;
        while ((wave_map[i][j] != 0) && (!((i == height - 1) && (j == width - 1) && (wave_map[i-1][j] == -1) && (wave_map[i][j-1] == -1)))){
            top++;
            stack[top] = i*width+j;
            int flag = 0;
            if ((i+1 < height) && (wave_map[i+1][j] == wave_map[i][j] - 1) && (((*map)[i][j]).bottom != WALL)) {
                if ((i != height - 1) && (j != width - 1)) wave_map[i][j] = -1;
                i = i+1;
                flag = 1;
            }
            else if ((i-1 >= 0) && (wave_map[i-1][j] == wave_map[i][j] - 1) && (((*map)[i-1][j]).bottom != WALL)) {
                if ((i != height - 1) && (j != width - 1)) wave_map[i][j] = -1;
                i = i-1;
                flag = 1;
            }
            else if ((j+1 < width) && (wave_map[i][j+1] == wave_map[i][j] - 1) && (((*map)[i][j]).right != WALL)) {
                if ((i != height - 1) && (j != width - 1)) wave_map[i][j] = -1;
                j = j+1;
                flag = 1;
            }
            else if ((j-1 >= 0) && (wave_map[i][j-1] == wave_map[i][j] - 1) && (((*map)[i][j-1]).right != WALL)) {
                if ((i != height - 1) && (j != width - 1)) wave_map[i][j] = -1;
                j = j-1;
                flag = 1;
            }
            if (!flag) {
            while (stack[top] != -1) top--;
                i = height - 1;
                j = width - 1;
            }
        }
        while ((stack[top] != -1) && (top >= 0)) {
            if (width >= height)((*map)[stack[top]/width][stack[top]%width]).isPartOfPath = PATH;
            else ((*map)[stack[top]/height][stack[top]%height]).isPartOfPath = PATH;
            top--;
        }
        ((*map)[0][0]).isPartOfPath = PATH;
        maze_path_print(*map, height, width);
        free(stack);
        }
        free_matrix((void***)map, height);
        free_matrix((void***)(&wave_map), height);
    }
}
int wave_map_filling_for_maze(int** wave_map, maze_cell** map, int height, int width) {
    int wave_counter = 0, wave_spreading_counter = 1,flag = 0;
    while ((wave_spreading_counter != 0) && !flag) {
        wave_spreading_counter = 0;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++) {
                wave_map_step_for_maze(wave_map,map,height,width,i,j, wave_counter,&flag,&wave_spreading_counter);
            }
        }
        wave_counter++;
    }
    if (!flag) printf("Путь не найден!\n");
    return flag;
}
void wave_map_step_for_cave(int** wave_map, cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter) {
    if (wave_map[i][j] == wave_counter) {
        for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
                if ((i+k < 0) || (i+k >= height) || (j+l < 0) || (j+l >= width) || ((l == 0) && (k == 0)) || (map[i+k][j+l] == WALL)) continue;
                if (wave_map[i+k][j+l] == -1) {
                    (*wave_spreading_counter)++;
                    wave_map[i+k][j+l] = wave_counter + 1;
                    if ((i+k == height - 1) && (j+l == width - 1)) *flag = 1;
                }
            }
        }
    }
}
void wave_map_step_for_maze(int** wave_map, maze_cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter) {
    if (wave_map[i][j] == wave_counter) {
        if ((i+1 < height) && ((map[i][j]).bottom != WALL)) {
            if (wave_map[i+1][j] == -1) {
                (*wave_spreading_counter)++;
                wave_map[i+1][j] = wave_counter + 1;
                if ((i+1 == height - 1) && (j == width - 1)) *flag = 1;
            }
        }
        if ((i-1 >= 0) && ((map[i-1][j]).bottom != WALL)) {
            if (wave_map[i-1][j] == -1) {
                (*wave_spreading_counter)++;
                wave_map[i-1][j] = wave_counter + 1;
            }
        }
        if ((j+1 < width) && ((map[i][j]).right != WALL)) {
            if (wave_map[i][j+1] == -1) {
                (*wave_spreading_counter)++;
                wave_map[i][j+1] = wave_counter + 1;
                if ((i == height - 1) && (j + 1 == width - 1)) *flag = 1;
            }
        }
        if ((j-1 >= 0) && ((map[i][j-1]).right != WALL)) {
            if (wave_map[i][j-1] == -1) {
                (*wave_spreading_counter)++;
                wave_map[i][j-1] = wave_counter + 1;
            }
        }
    }
}
