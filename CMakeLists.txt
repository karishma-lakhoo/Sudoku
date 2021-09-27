cmake_minimum_required(VERSION 3.16)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
add_executable(tests tests.cpp sub01.cpp MyStackV.cpp)
#add_executable(9x9_sudoku_solver 9x9_sudoku_solver.cpp MyStackV.cpp)
add_executable(9x9_sudoku_solver sub01.cpp)

#add_executable(MyStackV MyStackV.cpp)
add_executable(safekeeping safekeeping.cpp)


add_executable(16x16_sudoku_solver 16x16_sudoku_solver.cpp)
add_executable(25x25_sudoku_solver 25x25_sudoku_solver.cpp)