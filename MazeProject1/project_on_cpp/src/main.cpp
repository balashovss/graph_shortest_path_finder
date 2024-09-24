
#include "maze_gen_funcs.h"
#include "path_planning_algs.h"
#include "matrix_funcs.h"
void console_app(int type) {
    int height, width;
    if (type == CAVE_GEN) {
        cell** map = (cell**)generate_map(&height, &width, CAVE_GEN);
        wave_algorithm_for_cave(&map, height, width);
    }
    else {
        maze_cell** map = (maze_cell**)generate_map(&height, &width, MAZE_GEN);
        wave_algorithm_for_maze(&map, height, width);
    }
}
int main(int argc, char* argv[]) {
    if ((argc == 2) && ((atoi(argv[1]) == CAVE_GEN) || (atoi(argv[1]) == MAZE_GEN))) {
        console_app(atoi(argv[1]));
    }
    //FILE* fptr = fopen("maps/maps.txt", "a+");
    return 0;
}
