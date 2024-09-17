#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
void fill_map(cell** map, int height, int width, int alive_probability) {
    srand(time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand()%100 < alive_probability) map[i][j] = MOVABLE;
        }//0 is for wall, 1 is for mov
    }
}
void matrix_print(cell** map, int height, int width) {
    int flag = 0;
    for (int i = 0; ((i < height) && (!flag)); i++) {
        for (int j = 0; ((j < width) && (!flag)); j++) {
            switch (map[i][j]){ 
                case WALL: printf("0");
                break;
                case MOVABLE:printf(" ");
                break;
                default: 
                flag = 1;
                break;
            }    
        }//0 is for wall, 1 is for mov
        printf("\n");
    }
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
int main() {
    int width, height;
    char c;
    printf("Введите размеры карты как два целых числа(ширина, высота) c любым разделителем(не выходите пж за пределы оперативки)\n");
    if (scanf("%d %c %d",&width, &c, &height) != 3) {
        printf("n/a");
    }
    else {
    cell** map = create_matrix(height, width);
    int alive_probability = 45;
    fill_map(map, height, width, alive_probability);
    matrix_print(map, height, width);
    free_matrix(&map, height);
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    }
    return 0;
}