#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <stack>
#include <cmath>
#include <math.h>
#include "mysudoku.h"
#include <unordered_set>
//#include "9x9_sudoku_solver.h"

//this is to define the size od the 2D matrix (N*N) which is 9
#define N 9
#define BLANK 0
#define SPACE " "
#define ROWS 9
#define COLUMNS 9
#define EMPTY 0



using namespace std;


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
bool safeInRow(int Array[N][N], int row, int value){
    for(int col = 0; col < N; col++){
        if(Array[row][col] == value){
            return false;
        }
    }
    return true;
}

//returns a boolean operator to indicate if is the value already exists in the column
bool safeInCol(int Array[N][N], int col, int value){
    for(int row = 0; row < N; row++){
        if(Array[row][col] == value){
            return false;
        }
    }
    return true;
}

//returns a boolean operator to indicate if is the value already exists in the block or variable size
bool safeInBlock(int Array[N][N], int blockRowIndex, int blockColIndex, int value){
    int blockWidthHeight = pow(N, 0.5);
//we need to find out which block to look in based on the coordinates we are given
    int blockRowStart = blockRowIndex - (blockRowIndex + blockWidthHeight) % blockWidthHeight;
    int blockColStart = blockColIndex - (blockColIndex + blockWidthHeight) % blockWidthHeight;

//once we found the specified block then we can search if the value exists the block
    for(int row = 0; row < blockWidthHeight; row++){
        for (int col = 0; col < blockWidthHeight; col++){
            if(Array[blockRowStart + row][blockColStart + col] == value)
            {
                return false;
            }
        }
    }
    return true;
}

//check if its safe to assign a value here
bool isSafeCell(int Array[N][N],int RowIndex,int ColIndex, int value){
    bool rowCheck = safeInRow(Array, RowIndex, value);
    bool colCheck = safeInCol(Array, ColIndex, value);
    bool blockCheck = safeInBlock(Array, RowIndex, ColIndex, value);
    if(rowCheck && colCheck && blockCheck){
        return false;
    }
    else{
        return true;
    }
}

//finding all the EMPTY spaces in the sudoku
//create 3 2D arrays - one for the EMPTY spaces in the rows, columns and blocks
//the function should return the count of the number of EMPTY spaces in each

// this returns just the number of zeros in the specified row

int numberOfUnknownsInRow(int Array[N][N], int rowNumber){
    int count = 0;
    for(int col = 0; col < N; col++){
        if(Array[rowNumber][col] == EMPTY){
            count += 1;
        }
    }
    return count;
}



// this returns just the number of zeros in the specified col
int numberOfUnknownsInCol(int Array[N][N], int colNumber){
    int count = 0;
    for(int row = 0; row < N; row++){
        if(Array[row][colNumber] == EMPTY){
            count += 1;
        }
    }
    return count;
    }

//this returns just the number of zeros in the specified block
int numberOfUnknownsInBlock(int Array[N][N], int blockRowIndex, int blockColIndex){
    int count = 0;
    int blockWidthHeight = pow(N, 0.5);
//we need to find out which block to look in based on the coordinates we are given
    int blockRowStart = blockRowIndex - (blockRowIndex + blockWidthHeight) % blockWidthHeight;
    int blockColStart = blockColIndex - (blockColIndex + blockWidthHeight) % blockWidthHeight;

//once we found the specified block then we can search if the value exists the block
    for(int row = 0; row < blockWidthHeight; row++){
        for (int col = 0; col < blockWidthHeight; col++){
            if(Array[blockRowStart + row][blockColStart + col] == EMPTY)
            {
                count += 1;
            }
        }
    }
    return count;
}


// this searches the array and looks for all the EMPTY cells within the sudoku
// it returns 3 integers namely the row and col coordinates as well as the value, which is zero in this case

//i need to check for what to do if this vector is empty

vector<Test> findEmptyCellsLocation(int Array[N][N]) {
    vector<Test> emptyCellsLocationVector;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (Array[row][col] == EMPTY) {
                emptyCellsLocationVector.push_back({row, col, EMPTY});
            }
        }
    }
    return emptyCellsLocationVector;
}


// this function sums the relevant row col and block ranks for a specific cell
int RankOfCell(int Array[N][N], int rowIndex, int colIndex){
    int rowRank = numberOfUnknownsInRow(Array, rowIndex);
    int colRank = numberOfUnknownsInCol(Array, colIndex);
    int blockRank = numberOfUnknownsInBlock(Array, rowIndex, colIndex);
    int cellRank = rowRank + colRank + blockRank;
    return cellRank;
}

//    but i only need to do this for the cells with zeros in it
//        and i need to set the rest of the matrix to null values
// this function has the ranks of all the unassigned values amongst zeros in a 2D array
vector<vector<Test>> rankSudoku(int Array[N][N]){
//    here im initialising the array with zero values
    vector<vector<Test>> rankSudokuVector (9,vector<Test>(9));
    for(int i = 0; i < rankSudokuVector.size(); ++i){
        for(int j = 0; j < rankSudokuVector[i].size(); ++j){
            rankSudokuVector[i][j].numberValue = 0;
        }
    }

// now to replace the zero values with the ranks
    vector<Test> emptyCellsLocationVector;
    emptyCellsLocationVector = findEmptyCellsLocation(Array);
    for(int i = 0; i < emptyCellsLocationVector.size(); i++){
        Test unassignedRank = emptyCellsLocationVector[i];
        rankSudokuVector[unassignedRank.rowCoordinate][unassignedRank.colCoordinate].rowCoordinate \
        = unassignedRank.rowCoordinate;
        rankSudokuVector[unassignedRank.rowCoordinate][unassignedRank.colCoordinate].colCoordinate \
        = unassignedRank.colCoordinate;
        rankSudokuVector[unassignedRank.rowCoordinate][unassignedRank.colCoordinate].numberValue \
        = RankOfCell(Array, unassignedRank.rowCoordinate, unassignedRank.colCoordinate);
    }
    return rankSudokuVector;
}


// finding the lowest value rank matrix, whilst ignoring the zeros since those are the known values
Test bestCell(vector<vector<Test>> rankSudoku){
    Test t;
    t.numberValue = rankSudoku[0][0].numberValue;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(rankSudoku[i][j].numberValue != 0){
                if(rankSudoku[i][j].numberValue < t.numberValue){
                    t.rowCoordinate = i;
                    t.colCoordinate = j;
                    t.numberValue = rankSudoku[i][j].numberValue;
                }
            }
        }
    }

    return t;
}

// now to find the candidates in each row, col or block
vector<int> candidateInRow(int Array[N][N], int RowIndex){

    unordered_set<int> s;
    vector<int> candidateVect;
    for(int i = 0; i< N; i++){
        s.insert(Array[RowIndex][i]);
    }

    for(int x = 1; x < N+1; x++){
        if(s.find(x) == s.end()){
            candidateVect.push_back(x);
        }
    }
    return candidateVect;
}

vector<int> candidateInCol(int Array[N][N], int ColIndex){

    unordered_set<int> s;
    vector<int> candidateVect;
    for(int i = 0; i< N; i++){
        s.insert(Array[i][ColIndex]);
    }

    for(int x = 1; x < N+1; x++){
        if(s.find(x) == s.end()){
            candidateVect.push_back(x);
        }
    }
    return candidateVect;
}

vector<int> candidateInBlock(int Array[N][N], int blockRowIndex, int blockColIndex){
    unordered_set<int> s;
    vector<int> candidateVect;

    int blockWidthHeight = pow(N, 0.5);
//we need to find out which block to look in based on the coordinates we are given
    int blockRowStart = blockRowIndex - (blockRowIndex + blockWidthHeight) % blockWidthHeight;
    int blockColStart = blockColIndex - (blockColIndex + blockWidthHeight) % blockWidthHeight;

//once we found the specified block then we can search if the value exists the block
    for(int row = 0; row < blockWidthHeight; row++){
        for (int col = 0; col < blockWidthHeight; col++){
            s.insert(Array[blockRowStart + row][blockColStart + col]);
        }
    }


    for(int x = 1; x < N+1; x++){
        if(s.find(x) == s.end()){
            candidateVect.push_back(x);
        }
    }
    return candidateVect;
}


//candidates in cell using the 3 functions above
vector<int> candidateInCell(int Array[N][N], int RowIndex, int ColIndex){
    vector<int> rowCandidates = candidateInRow(Array, RowIndex);
    vector<int> colCandidates = candidateInCol(Array, ColIndex);
    vector<int> blockCandidates = candidateInBlock(Array, RowIndex, ColIndex);

    sort(rowCandidates.begin(), rowCandidates.end());
    sort(colCandidates.begin(), colCandidates.end());
    sort(blockCandidates.begin(), blockCandidates.end());

    vector<int> common1;
    vector<int> commonFinal;

//    common elements in the row and col candidates
    set_intersection(rowCandidates.begin(),rowCandidates.end(), colCandidates.begin(), colCandidates.end(),
                     back_inserter(common1));
    set_intersection(blockCandidates.begin(),blockCandidates.end(), common1.begin(), common1.end(),
                     back_inserter(commonFinal));
    return commonFinal;
    }
template<typename T>
void popFrontIntVector(vector<T>& vec)    {
    assert(!vec.empty());
    vec.erase(vec.begin());
}



bool solve(int Array[N][N]){

//    im initialising the stack here
    MyStackV mySudokuStack;


// so when the grid is not already solved, the continue to search and find values
// this is the number of empty cells in the sudoku
    int numberOfEmptyCells = findEmptyCellsLocation(Array).size();
    if(numberOfEmptyCells == 0){
        return true;
    }
    else{
//      Initialising the Rank Grid
        vector<vector<Test>> mySudokuRank (N,vector<Test>(N));
        mySudokuRank = rankSudoku(Array);
//        i think this part is wrong, since its only going to do this a for the number of empty cells that there is
        for(int emptyCellIterator = 0; emptyCellIterator < numberOfEmptyCells; emptyCellIterator++){
            Test bestCellChoice = bestCell(mySudokuRank);
            int bestCellChoiceRow = bestCellChoice.rowCoordinate;
            int bestCellChoiceCol = bestCellChoice.colCoordinate;
//            initialising the vector of candidates for the best cell
            vector<int> candidatesForBestCell = candidateInCell(Array, bestCellChoiceRow, bestCellChoiceCol);

//          now to change the value to the first candidate
            Array[bestCellChoiceRow][bestCellChoiceCol] = candidatesForBestCell.front();

//          add this value and its index to the stack
            mySudokuStack.push(bestCellChoiceRow, bestCellChoiceCol, candidatesForBestCell.front());

//          now to update rank grid and the best cell choice so i can move to next cell
            mySudokuRank = rankSudoku(Array);
            Test bestCellChoice2 = bestCell(mySudokuRank);
            int bestCellChoiceRow2 = bestCellChoice2.rowCoordinate;
            int bestCellChoiceCol2 = bestCellChoice2.colCoordinate;
//            initialising the vector of candidates for the best cell
            vector<int> candidatesForBestCell2 = \
                    candidateInCell(Array, bestCellChoiceRow2, bestCellChoiceCol2);
//            if i placed the wrong candidate choice in the cell and i need to backtrack
//          i think its the wrong choice if the next cell has no candidates
//          (but there would also be no candidates in the case where the grid is full)
            if(candidatesForBestCell2.empty()){
                if(findEmptyCellsLocation(Array).empty()){
                    return true;
                }
                mySudokuStack.pop();
//                to pop_front the first element in the candidate vector of the fist element we inserted
                for(int i = 0; i < candidatesForBestCell.size() - 1; i++){
                    candidatesForBestCell[i] = popFrontIntVector(candidatesForBestCell)[i]
                }
//                retry with the next candidate in the list

                }
            else{
                continue;
            }
        }
    }





//        i need to do a case where i update the number of empty cells


}



// now use the indicies of the lowest value and allocate it a value

// Add this value to the stack


// you can just re calc the rank array instead of updating it




//    this value needs to be safe in the row col and specified block, if its not, then pop from the stack

//      to make sure that the value is safe, we need to make sure the number is not in the row, col or block

//          you need to make a case for a no solution sudoku - the rank matrix is equal to zero


//  once all the values are complete


// check if the fixed cells are valid in the grid



// output the complete sudoku












//remember to code for a no solution case


int main(){
    int inputArray[ROWS][COLUMNS];
    fillArray(inputArray);
    printArray(inputArray);

    cout << "row, col 8 and block" << endl;
    cout << numberOfUnknownsInRow(inputArray, 8) << endl;
    cout << numberOfUnknownsInCol(inputArray, 8) << endl;
    cout << "block 9" << endl;
    cout << numberOfUnknownsInBlock(inputArray, 7, 7) << endl;

//    vector<Test> asdf;
//    asdf = findEmptyCellsLocation(inputArray);
//    cout << asdf.size() << endl;
//    cout << endl;
//    for(int i = 0; i < asdf.size(); i++){
//        cout << asdf[i].rowCoordinate << ", " << asdf[i].colCoordinate
//             << ", " << asdf[i].numberValue << endl;
//    }
    cout << endl;
    cout << "this is just to test the empty cells location funciton" << endl;
    vector<Test> emptyCellVect;
    emptyCellVect = findEmptyCellsLocation(inputArray);
    cout << emptyCellVect.size() << endl;
    for(int i = 0; i < emptyCellVect.size(); i++){
        cout << emptyCellVect[i].numberValue << " " << emptyCellVect[i].rowCoordinate << " " << emptyCellVect[i].colCoordinate << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    vector<int> CandidateRVector;
    vector<int> CandidateCVector;
    vector<int> CandidateBVector;
    vector<int> CandidateCellVector;
    cout << "row candidates in row 2 - index 1" << endl;
    CandidateRVector = candidateInRow(inputArray, 1);
    for(int i = 0; i < CandidateRVector.size(); ++i) {
        cout << CandidateRVector[i] << " ";
    }
    cout << endl;

    cout << "col candidates in col 7 - index 6" << endl;
    CandidateCVector = candidateInCol(inputArray, 6);
    for(int i = 0; i < CandidateCVector.size(); ++i) {
        cout << CandidateCVector[i] << " ";
    }
    cout << endl;

    cout << "block candidates in block 3" << endl;
    CandidateBVector = candidateInBlock(inputArray, 1, 6);
    for(int i = 0; i < CandidateBVector.size(); ++i) {
        cout << CandidateBVector[i] << " ";
    }
    cout << endl;
    cout << "candidates in cell [1][6]" << endl;
    CandidateCellVector = candidateInCell(inputArray, 1, 6);
    for(int i = 0; i < CandidateCellVector.size(); ++i) {
        cout << CandidateCellVector[i] << " ";
    }
    cout << endl;
    cout << "-------------" << endl;
    cout << endl;
    cout << endl;
    cout << "this is printing the rank 2D Array" << endl;
    cout << "asdf" << endl;
    vector<vector<Test>> mySudokuRank (9,vector<Test>(9));
    mySudokuRank = rankSudoku(inputArray);

    for(int i = 0; i < mySudokuRank.size(); ++i) {
        for(int j = 0; j < mySudokuRank[i].size(); ++j) {
            cout << mySudokuRank[i][j].numberValue << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "________________________" << endl;
    cout << endl;
    cout << "location of best cell and associated value" << endl;
    Test bestCellAndValue;
    bestCellAndValue = bestCell(rankSudoku(inputArray));
    cout << bestCellAndValue.rowCoordinate << " " << bestCellAndValue.colCoordinate << " " << \
    bestCellAndValue.numberValue << endl;



//    for(int i = 0; i < N; i++){
//        cout << ptrNumberOfUnknownsRows(inputArray)[i] << endl;
//    }


//    MyStackV mySudokuStack;
//
//    int rowCoordinate = 0;
//    int colCoordinate = 2;
//    int cellValue = 3;
//
//    mySudokuStack.push(rowCoordinate, colCoordinate, cellValue);
//    Test *topOfStack;
//    topOfStack = &mySudokuStack.peek();
//    cout << "after pushing size" << endl;
//    cout << mySudokuStack.size() << endl;
//    cout << topOfStack->x << endl;
//    cout << topOfStack->y << endl;
//    cout << topOfStack->z << endl;
//
//    mySudokuStack.pop();
//
//
//
//
//
//
//
//    if(used_in_block(inputArray, 0, 7, 7)){
//        cout << "asdf" << endl;
//    }
    return 0;
}