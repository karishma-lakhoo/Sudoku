#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <fstream>
#include <stack>
#include <cmath>
#include "mysudoku.h"

using namespace std;

//i wasnt coming right with the stacks function so i made my own stack
void MyStackV::push(int x,int y,int z)
{
    data.push_back({x, y, z});
}

void MyStackV::pop()
{
    data.pop_back();
}

Test &MyStackV::peek()
{
    data.back();
}

size_t MyStackV::size() const
{
    data.size();
}

bool MyStackV::empty() const
{
    if(data.empty()){
        return true;
    }
}
