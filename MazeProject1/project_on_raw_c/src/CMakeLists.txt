cmake_minimum_required(VERSION 3.5.0)
project(CaveProject VERSION 0.1.0 LANGUAGES C CXX)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GoogleTest REQUIRED gtest gtest_main)
add_executable(CaveProject main.c matrix_funcs.c maze_gen_funcs.c path_planning_algs.c)
include(CTest)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
