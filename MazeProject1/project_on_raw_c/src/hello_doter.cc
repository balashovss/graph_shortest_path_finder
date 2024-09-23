#include <gtest/gtest.h>

#include <cmath>

#include "path_planning_algs.h"
#include "maze_gen_funcs.h"
#include "matrix_funcs.h"

TEST(Generator, gen1) {
    int height = 5;
    int width = 5;
    void*** map = NULL;
    for (int i = 0; i < 100; i++) {
        generate_maze((void***)map, height, width);
        wave_algorithm_for_maze((void***)map, height, width);
        free_matrix((void***)map, height);
    }
};


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}