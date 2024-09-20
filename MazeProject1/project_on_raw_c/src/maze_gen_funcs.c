#include "maze_gen_funcs.h"
#include "matrix_funcs.h"



int aliveness_counter(cell** map, int height, int width) {
    int alive_counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == WALL) alive_counter++;
        }
    }
    return alive_counter;
}
void fill_map(cell** map, int height, int width) {
    srand(time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand()%100 < ALIVE_PROBABILITY) map[i][j] = WALL;
            else map[i][j] = MOVABLE;
        }//0 is for wall, 1 is for mov
    }
}
int aliveNeighbours(cell** map, int height, int width, int i, int j) {
    int alive_counter = 0;
    for (int k = -1; k < 2; k++) {
        for (int l = -1; l < 2; l++) {
            if ((k == 0 && l == 0) || (i + k < 0) || (i + k >= height) || (j + l < 0) || (j + l >= width)) continue;
            if (map[i + k][j + l] == MOVABLE) alive_counter++;
        }
    }
    return alive_counter;
}
void check_aliveness(cell** map, cell** next_iteration_map_, int i, int j, int height, int width) {
    int aliveNeighbours_ = aliveNeighbours(map, height, width, i, j);
    if (map[i][j] == WALL) {
        if ((aliveNeighbours_ <= SURVIVING) && (aliveNeighbours_ != 0)) next_iteration_map_[i][j] = WALL;
        else next_iteration_map_[i][j] = MOVABLE;
    }
    else {
        if (aliveNeighbours_ == BIRTHING) next_iteration_map_[i][j] = WALL;
        else next_iteration_map_[i][j] = MOVABLE;
    }
}
void next_iteration_map(cell** map, int height, int width) {
    cell** next_iteration_map_ = (cell**)create_matrix(height, width,CELL_TYPE);
    fill_map(next_iteration_map_, height, width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            check_aliveness(map, next_iteration_map_, i, j, height, width);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = next_iteration_map_[i][j];
        }
    }
    free_matrix((void***)(&next_iteration_map_),height);
}
void cellular_automata_cycle(cell** map, int height, int width) {
    //int number_of_iterations = 3;
    while (aliveness_counter(map,height,width) >= NEEDED_NUMBER_OF_WALLS){
        cave_print(map, height, width);
        next_iteration_map(map, height, width);
    }
    map[0][0] = MOVABLE;
    map[height - 1][width - 1] = MOVABLE;
    printf("Исходный лабиринт:\n");
    cave_print(map, height, width);
}
void** generate_maze(int* height, int* width, int type) {
    cell** map = NULL;
    printf("Введите размеры карты как два целых числа(ширина, высота) c любым разделителем(не выходите пж за пределы оперативки)\n");
    if ((scanf("%d%d",width, height) != 2) || (*width <= 0) || (*height <= 0)) {
        printf("n/a");
    }
    else {
        if (type == CAVE_GEN) {
            map = (cell**)create_matrix(*height, *width, CELL_TYPE);
            fill_map(map, *height, *width);
            int number_of_iterations = 0;
            while (aliveness_counter(map, *height, *width) <= NEEDED_NUMBER_OF_WALLS_ON_GEN) {
                fill_map(map, *height, *width);
                printf("number of generation iterations: %d\n", ++number_of_iterations);
            }
            cellular_automata_cycle(map, *height, *width);
    //FILE* fptr = fopen("maps/maps.txt", "a+");
            }
        else if (type == MAZE_GEN) {
            maze_cell* tmp = (maze_cell*)malloc(sizeof(maze_cell)*(*width));
            maze_cell** map = (maze_cell**)create_matrix((*height), (*width), MAZE_CELL_TYPE);
            srand(time(NULL));
            for (int i = 0; i < (*height) - 1; i++) {
                if (i == 0) {
                for (int j = 0; j < (*width); j++) {
                    (tmp[j]).set = 1+j+i*(*height);
                    (tmp[j]).right = MOVABLE;
                    (tmp[j]).bottom = MOVABLE;
                }
                }
                for (int j = 0; j < (*width) - 1; j++) {
                    unsigned char maybe_right_wall = (unsigned char)(rand()%2);
                    if ((maybe_right_wall == WALL) || ((tmp[j]).set == (tmp[j+1]).set)) (tmp[j]).right = WALL;
                    else {
                        int temp = (tmp[j+1]).set;
                        for (int k = 0; k < (*width); k++) {
                            if ((tmp[k]).set == temp) (tmp[k]).set = (tmp[j]).set; 
                        }
                    }
                }
                tmp[(*width) - 1].right = WALL;
                for (int j = 0; j < (*width); j++) {
                    unsigned char maybe_bottom_wall = (unsigned char)(rand()%2);
                    if (maybe_bottom_wall == WALL) {
                        int count = 0;
                        for (int k = 0; k < (*width);k++) {
                            if (((tmp[k]).set == (tmp[j]).set) && ((tmp[k]).bottom != WALL)) count++;
                        }
                        if (count >= 2) (tmp[j]).bottom = WALL; 
                    }
                }
                for (int j = 0; j < (*width); j++) map[i][j] = tmp[j];
                if (i != *height - 2) {
                    for (int j = 0; j < (*width); j++) {
                        (tmp[j]).right = MOVABLE;
                        if ((tmp[j]).bottom == WALL) {
                            (tmp[j]).set = (i+1)*(*height) + j + 1;
                            (tmp[j]).bottom = MOVABLE;
                        }
                    }
                }
                else {
                    for (int j = 0; j < (*width) - 1; j++) {
                        (tmp[j]).bottom = WALL;
                        if (((tmp[j]).right == WALL) && ((tmp[j]).set != (tmp[j+1]).set)) {
                            int temp = (tmp[j+1]).set;
                            for (int k = j+1; k < (*width); k++) {
                                if ((tmp[k]).set == temp) (tmp[k]).set = (tmp[j]).set; 
                            }
                            tmp[j].right = MOVABLE;
                        }
                    }
                    tmp[(*width) - 1].bottom = WALL;
                }
                }
                for (int j = 0; j < (*width); j++) {
                    map[(*height) - 1][j] = tmp[j];
                }
                free(tmp);
                maze_print(map, *height, *width);
            }
    return (void**)map;
    }
}