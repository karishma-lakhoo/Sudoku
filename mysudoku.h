#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <map>

#ifndef SUDOKU_MYSUDOKU_H
#define SUDOKU_MYSUDOKU_H

using namespace std;

class Item{
public:
    int rowCoordinate;
    int colCoordinate;
    int numberValue;
};

struct Test
{
    int x, y, z;
};


class MyStackV
{
public:
    void push(int x, int y, int z);
    void pop();

    Test& peek();

    size_t size() const;
    bool empty() const;

protected:
    std::vector<Test> data;
};









#endif //SUDOKU_MYSUDOKU_H
