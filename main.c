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
    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            if (map[i][j] == MOVABLE) {
                int flag = 0;
                for (int k = -1; k < 2; k++) {
                    for (int z = -1; z < 2; z++) {
                        if (!(k == 0 && z == 0)) flag = map[i+k][j+z] == MOVABLE;
                    }
                }
                if (!flag) {
                    int tmp_x = rand()%3 - 1;
                    int tmp_y = rand()%3 - 1;
                    if (tmp_x == 0 && tmp_y == 0) tmp_x++;
                    map[i+tmp_x][j+tmp_y] = MOVABLE;
                }
            }
        }
    }
    //Вывод
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (map[i][j]){ 
                case WALL: printf("0");
                break;
                case MOVABLE:printf(" ");
                break;
                }    
        }//0 is for wall, 1 is for mov
        printf("\n");
    }
    //Высвобождение памяти
    for (int i = 0; i < width; i++) {
        free(map[i]);
    }
    free(map);
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    }
    return 0;
}