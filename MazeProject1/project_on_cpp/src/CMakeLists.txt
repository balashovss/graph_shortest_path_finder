cmake_minimum_required(VERSION 3.5.0)
project(CaveProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(CaveProject main.cpp matrix_funcs.cpp maze_gen_funcs.cpp path_planning_algs.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
