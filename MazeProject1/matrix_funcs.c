#include <stdlib.h>
#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
void** create_matrix(int height, int width, int regime) {
    void** map = NULL;
    switch (regime) {
        case CELL_TYPE:
            map = malloc(sizeof(cell*) * height);
            for (int i = 0; i < height; i++) map[i] = (cell*) malloc(sizeof(cell) * width);
            break;
        case INT_TYPE:
            map = malloc(sizeof(int*)*height);
            for (int i = 0; i < height; i++) map[i] = (int*)malloc(sizeof(int)*width);
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
void maze_print(cell** map, int height, int width) {
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
                case WALL: printf("0");
                break;
                case MOVABLE:printf(" ");
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