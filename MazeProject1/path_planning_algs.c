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
void wave_map_step(int** wave_map, cell** map, int height, int width, int i, int j, int wave_counter, int* flag, int* wave_spreading_counter) {
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
void wave_map_filling(int** wave_map, cell** map, int height, int width) {
    int wave_counter = 0, wave_spreading_counter = 1,flag = 0;
    while ((wave_spreading_counter != 0) && !flag) {
        wave_spreading_counter = 0;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++) {
                wave_map_step(wave_map,map,height,width,i,j, wave_counter,&flag,&wave_spreading_counter);
            }
        }
        wave_counter++;
    }
    if (!flag) printf("Путь не найден!\n");
}
void wave_algorithm(cell*** map, int height, int width){
    if (*map != NULL) {
        int** wave_map = wave_map_init(height, width);
        wave_map_filling(wave_map, *map, height, width);
        print_waves(wave_map, height, width);
        int* stack = malloc(sizeof(int)*height*width);
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
        while (stack[top] != -1) {
            printf("%d ", stack[top]);
            top--;
        }            
        free(stack);
        free_matrix((void***)map, height);
        free_matrix((void***)(&wave_map), height);
    }
}