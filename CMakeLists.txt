cmake_minimum_required(VERSION 3.16)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sudoku main.cpp)
add_executable(tests tests.cpp mysudoku.h)
add_executable(9x9_sudoku_solver 9x9_sudoku_solver.cpp)
