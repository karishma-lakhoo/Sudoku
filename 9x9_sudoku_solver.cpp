#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <fstream>
#include <stack>
#include <cmath>
#include "mysudoku.h"

//this is to define the size od the 2D matrix (N*N) which is 9
#define N 9
#define BLANK 0
#define SPACE " "
#define ROWS 9
#define COLUMNS 9

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


//function that reads in the input and converts the values stored in the rows and columns into an array
void fillArray(int inputArray[ROWS][COLUMNS]){
    for(int i = 0; i < ROWS; i ++){
        for(int j = 0 ; j < COLUMNS; j++){
            cin >> inputArray[i][j];
        }
    }
}

//this is to print the array out at the end
void printArray(int Array[ROWS][COLUMNS]){
    for(int i =0; i < ROWS; i++){
        for(int j=0; j < COLUMNS; j++){
            cout << Array[i][j] << " ";
        }
        cout << endl;
    }
}


//returns a boolean operator to indicate if is the value already exists in the row
bool used_in_row(int Array[N][N], int row, int value){
    for(int col = 0; col < N; col++){
        if(Array[row][col] == value){
            return true;
        }
    }
    return false;
}

//returns a boolean operator to indicate if is the value already exists in the column
bool used_in_col(int Array[N][N], int col, int value){
    for(int row = 0; row < N; row++){
        if(Array[row][col] == value){
            return true;
        }
    }
    return false;
}

//returns a boolean operator to indicate if is the value already exists in the block or variable size
bool used_in_block(int Array[N][N], int blockRowIndex, int blockColIndex, int value){
    int blockWidthHeight = pow(N, 0.5);
//we need to find out which block to look in based on the coordinates we are given
    int blockRowStart = blockRowIndex - (blockRowIndex + blockWidthHeight) % blockWidthHeight;
    int blockColStart = blockColIndex - (blockColIndex + blockWidthHeight) % blockWidthHeight;

//once we found the specified block then we can search if the value exists the block
    for(int row = 0; row < blockWidthHeight; row++){
        for (int col = 0; col < blockWidthHeight; col++){
            if(Array[blockRowStart + row][blockColStart + col] == value)
            {
                return true;
            }
        }
    }
    return false;
}

//check if its safe to assign a value here
bool isSafeCell(int Array[N][N],int RowIndex,int ColIndex, int value){
    bool rowCheck = used_in_row(Array, RowIndex, value);
    bool colCheck = used_in_col(Array, ColIndex, value);
    bool blockCheck = used_in_block(Array, RowIndex, ColIndex, value);
    if(rowCheck && colCheck && blockCheck){
        return false;
    }
    else{
        return true;
    }
}



int main(){
    int inputArray[ROWS][COLUMNS];
    fillArray(inputArray);
    printArray(inputArray);



//    MyStackV asdfasdf;
//    vector<Test> pasta;
//    int rowCoord = 0;
//    int colCoord = 0;
//    int numVal = 0;
//    pasta.push_back({rowCoord, colCoord, numVal});
//
//    asdfasdf.push(asddf);

    MyStackV asdfasdf;
//    vector<Test> myvec;
//
//    myvec.push_back({7, 2, 3});

//    vector<Test> idkanymore;
    int a = 0;
    int b = 2;
    int c = 3;
//    idkanymore.push_back({1, 2, 3});
//
//    for(int i = 0; i < idkanymore.size(); i++){
//        cout << idkanymore[i].x << ", " << idkanymore[i].y
//             << ", " << idkanymore[i].z << endl;
//    }

    asdfasdf.push(a, b, c);
    Test *kk;
    kk = &asdfasdf.peek();
    cout << "after pushing size" << endl;
    cout << asdfasdf.size() << endl;
    cout << kk->x << endl;
    cout << kk->y << endl;
    cout << kk->z << endl;

    asdfasdf.pop();
//    cout << asdfasdf.peek();

//    MyStackV mySudokuStack;
//    Item *info = new Item();
//    info->rowCoordinate = 2;
//    info->colCoordinate = 1;
//    info->numberValue = 1;
//    mySudokuStack.push(reinterpret_cast<Item &>(info));
//
//
//    cout << mySudokuStack.peek();



//    stack<vector<tuple<int, int, int>>> mySudokuStack;
//    vector<tuple<int, int, int>> vectorOfTuples;
//    int rowCoordinate = 0;
//    int colCoordinate = 0;
//    int numberValue = 0;
//    vectorOfTuples.emplace_back(rowCoordinate, colCoordinate, numberValue);




//    mySudokuStack.push(vectorOfTuples);
//    vector<tuple<int, int, int>> aasdf;
//    aasdf = mySudokuStack.top();
//    for(int i = 0; i < aasdf.size(); i++){
//        cout << aasdf[i] << endl;
//    }


//    Item *a = new Item();
//
//    stack<array<int,int,int>> sudokuStack;
//    sudokuStack.push(a->rowCoordinate, a->colCoordinate, a->numberValue);




//    if(used_in_block(inputArray, 0, 7, 7)){
//        cout << "asdf" << endl;
//    }
    return 0;
}