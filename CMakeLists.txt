cmake_minimum_required(VERSION 3.16)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
add_executable(tests tests.cpp 9x9_sudoku_solver.cpp MyStackV.cpp)
add_executable(9x9_sudoku_solver 9x9_sudoku_solver.cpp MyStackV.cpp)

add_executable(MyStackV MyStackV.cpp)
add_executable(safekeeping safekeeping.cpp)
