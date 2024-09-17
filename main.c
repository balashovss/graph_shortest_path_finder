#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ALIVE_PROBABILITY 45
#define SURVIVING 2
#define BIRTHING 3
typedef enum cell{
    WALL,
    MOVABLE
}cell;
cell** create_matrix( int height, int width) {
    cell** map = (cell**) malloc(sizeof(cell*) * height);
    for (int i = 0; i < height; i++) {
        map[i] = (cell*) malloc(sizeof(cell) * width);
    }
    return map;
}
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
            if (rand()%100 < ALIVE_PROBABILITY) map[i][j] = MOVABLE;
        }//0 is for wall, 1 is for mov
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
void free_matrix(cell*** map, int height) {
    if (map != NULL) {
    for (int i = 0; i < height; i++) {
        free((*map)[i]);
    }
    free(*map);
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
void checkAliveness(cell** map, cell** next_iteration_map_, int i, int j, int height, int width) {
    int aliveNeighbours_ = aliveNeighbours(map, height, width, i, j);
    if (map[i][j] == WALL) {
        if (aliveNeighbours_ == SURVIVING) next_iteration_map_[i][j] = WALL;
        else next_iteration_map_[i][j] = MOVABLE;
    }
    else {
        if (aliveNeighbours_ == BIRTHING) next_iteration_map_[i][j] = WALL;
        else next_iteration_map_[i][j] = MOVABLE;
    }
}
cell** next_iteration_map(cell** map, int height, int width) {
    cell** next_iteration_map_ = create_matrix(height, width);
    fill_map(next_iteration_map_, height, width, 0);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            checkAliveness(map, next_iteration_map_, i, j, height, width);
        }
    }
    return next_iteration_map_;
}
void cellularAutomataCycle(cell** map, int height, int width) {
    int number_of_iterations = 2;
    for (int i = 0; i < number_of_iterations; i++) {
        maze_print(map, height, width);
        map = next_iteration_map(map, height, width);
    }
    map[0][0] = MOVABLE;
    map[height - 1][width - 1] = MOVABLE;
    maze_print(map, height, width);
}
int main() {
    int width, height;
    printf("Введите размеры карты как два целых числа(ширина, высота) c любым разделителем(не выходите пж за пределы оперативки)\n");
    if (scanf("%d%d",&width, &height) != 2) {
        printf("n/a");
    }
    else {
    cell** map = create_matrix(height, width);
    fill_map(map, height, width);
    cellularAutomataCycle(map, height, width);
    free_matrix(&map, height);
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    }
    return 0;
}