#include "matrix_funcs.h"
#include "maze_gen_funcs.h"

int main() {
    int height, width;
    cell** map = generate_maze(&height, &width);
    int** wave_map = (int**)create_matrix(height, width, INT_TYPE);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            wave_map[i][j] = -1;
        }
    }
    wave_map[0][0] = 0;
    int wave_counter = 0, wave_spreading_counter = 1,flag = 0;
    while ((wave_spreading_counter != 0) && !flag) {
        wave_spreading_counter = 0;
        printf("На месте\n");
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++) {
                if (wave_map[i][j] == wave_counter) {
                    for (int k = -1; k < 2; k++) {
                        for (int l = -1; l < 2; l++) {
                            if ((i+k < 0) || (i+k >= height) || (j+l < 0) || (j+l >= width) || ((l == 0) && (k == 0)) || (map[i+k][j+l] == WALL)) continue;
                            if ((k != 0) && (l != 0)) {
                                if ((map[i+k][j+l] == MOVABLE) && (wave_map[i+k][j+l] == -1)) {
                                        wave_spreading_counter++;
                                        wave_map[i+k][j+l] = wave_counter + 2;
                                        if ((i+k == height - 1) && (j+l == width - 1)) flag = 1;
                                }
                            }
                            else {
                                if ((map[i+k][j+l] == MOVABLE) && (wave_map[i+k][j+l] == -1)) {
                                        wave_spreading_counter++;
                                        wave_map[i+k][j+l] = wave_counter + 1;
                                        if ((i+k == height - 1) && (j+l == width - 1)) flag = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        wave_counter++;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", wave_map[i][j]);
        }
        printf("\n");
    }
    if (!flag) printf("Путь не найден!\n");
    free_matrix((void***)(&map), height);
    free_matrix((void***)(&wave_map), height);
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    return 0;
}