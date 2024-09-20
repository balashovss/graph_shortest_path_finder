#include <stdlib.h>
#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
void** create_matrix(int height, int width, int regime) {
    void** map = NULL;
    switch (regime) {
        case CELL_TYPE:
            map = (void**)malloc(sizeof(cell*) * height);
            for (int i = 0; i < height; i++) map[i] = (cell*) malloc(sizeof(cell) * width);
            break;
        case INT_TYPE:
            map = (void**)malloc(sizeof(int*)*height);
            for (int i = 0; i < height; i++) map[i] = (int*)malloc(sizeof(int)*width);
            break;
        case MAZE_CELL_TYPE:
            map = (void**)malloc(sizeof(maze_cell*)*height);
            for (int i = 0; i < height; i++) map[i] = (maze_cell*)malloc(sizeof(maze_cell)*width);
            break;
    }
    return map;
}
void free_matrix(void*** map, int height) {
    if (*map != NULL) {
    for (int i = 0; i < height; i++) {
        free((*map)[i]);
    }
    free(*map);
    }
}
void cave_print(cell** map, int height, int width) {
    int flag = 0;
    for (int i = -1; ((i <= height) && (!flag)); i++) {
        for (int j = -1; ((j <= width) && (!flag)); j++) {
            if (i < 0) {
                if (j < 0) printf("+");
                else if (j == width) printf("+");
                else printf("-");
            }
            else if (i == height) {
                if (j < 0) printf("+");
                else if (j == width) printf("+");
                else printf("-");
            }
            else {
            if ((j < 0) || (j == width)) printf("|");
            else {
            switch (map[i][j]){ 
                case WALL: printf("|");
                break;
                case MOVABLE:printf(" ");
                break;
                case PATH: printf("x");
                break;
                default: 
                flag = 1;
                break;
            }
            }
        }    
        }//0 is for wall, 1 is for mov
        printf("\n");
    }
    printf("\n\n\n\n\n");
}
void maze_print(maze_cell** map, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((map[i][j]).bottom == WALL) printf("_");
            else printf(" ");
            if ((map[i][j]).right == WALL) printf("|");
            else printf(" ");
        }
        printf("\n");
    }
    printf("\n\n\n\n\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", map[i][j].set);
        }
        printf("\n");
    }
}