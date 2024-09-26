#include <stdlib.h>
#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
void** create_matrix(int height, int width, TYPES regime) {
    void** map = NULL;
    switch (regime) {
        case CELL_TYPE:
        {
            cell** map1 = new cell*[height];
            for (int i = 0; i < height; i++) map1[i] = new cell[width];
            return (void**)map1;
            break;
        }
        case INT_TYPE:
        {
            int** map2 = new int*[height];
            for (int i = 0; i < height; i++) map2[i] = new int[width];
            return (void**)map2;
            break;
        }
        case MAZE_CELL_TYPE:
        {
            maze_cell** map3 = new maze_cell*[height];
            for (int i = 0; i < height; i++) map3[i] = new maze_cell[width];
            return (void**)map3;
            break;
        }
    }
    return (void**)map;
}
void free_matrix(void*** map, int height, TYPES regime) {
    if (*map != NULL) {
        switch (regime)
        {
            case CELL_TYPE:
                for (int i = 0; i < height; i++) delete[] (cell*)(*map)[i];
                delete [] (cell**)(*map);
                break;
            case INT_TYPE:
                for (int i = 0; i < height; i++) delete[] (int*)(*map)[i];
                delete [] (int**)(*map);
                break;
            case MAZE_CELL_TYPE:
                for (int i = 0; i < height; i++) delete[] (maze_cell*)(*map)[i];
                delete [] (maze_cell**)(*map);
                break;
        }
        *map = NULL;                
    }
}
void maze_path_print(maze_cell** map, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((map[i][j]).isPartOfPath == PATH) {
                printf("X");
            }
            else printf(" ");
        }
        printf("\n");
    }
}