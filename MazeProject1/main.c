#include "matrix_funcs.h"
#include "maze_gen_funcs.h"
#include "path_planning_algs.h"
void app() {
    int height, width;
    cell** map = generate_maze(&height, &width);
    wave_algorithm(&map, height, width);
}
int main() {
    app();
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    return 0;
}