
#include "maze_gen_funcs.h"
#include "path_planning_algs.h"
void console_app() {
    int height, width;
    cell** map = generate_maze(&height, &width, CAVE_GEN);
    wave_algorithm(&map, height, width);
}
int main() {
    console_app();
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    return 0;
}