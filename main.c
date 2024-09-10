#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum cell{
    WALL,
    MOVABLE
}cell;
//#include <iostream>
int main() {
    int width, height;
    printf("Введите размеры карты как два целых числа(ширина, высота) c любым разделителем(не выходите пж за пределы оперативки)\n");
    if (scanf("%d %d",&width, &height) != 2) {
        printf("n/a");
    }
    else {
    cell** map = (cell**) malloc(sizeof(cell*) * height);
    for (int i = 0; i < width; i++) {
        map[i] = (cell*) malloc(sizeof(cell)*width);
    }
    srand(time(NULL));
    for (int i = 0; i <height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = rand()%2; 
        }//0 is for wall, 1 is for mov
    }
    for (int i = 0; i <height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ",map[i][j]); 
        }//0 is for wall, 1 is for mov
        printf("\n");
    }
    for (int i = 0; i < width; i++) {
        free(map[i]);
    }
    free(map);
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    }
    return 0;
}