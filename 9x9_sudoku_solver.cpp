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

vector<vector<int>> ArrayToVector(int inputArray[ROWS][COLUMNS]){
    vector<vector<int>> inputVector(N, vector<int> (N, 0));
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLUMNS; ++j) {
            inputVector[i][j] = inputArray[i][j];
        }
    }
    return inputVector;
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


// print out the inputVector
void printVector(vector<vector<int>> &inputVector){
    for(int i =0; i < ROWS; i++){
        for(int j=0; j < COLUMNS; j++){
            cout << inputVector[i][j] << " ";
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

int numberOfUnknownsInRow(vector<vector<int>> inputVector, int rowNumber){
    int count = 0;
    for(int col = 0; col < N; col++){
        if(inputVector[rowNumber][col] == EMPTY){
            count += 1;
        }
    }
    return count;
}



// this returns just the number of zeros in the specified col
int numberOfUnknownsInCol(vector<vector<int>> &inputVector, int colNumber){
    int count = 0;
    for(int row = 0; row < N; row++){
        if(inputVector[row][colNumber] == EMPTY){
            count += 1;
        }
    }
    return count;
}

//this returns just the number of zeros in the specified block
int numberOfUnknownsInBlock(vector<vector<int>> &inputVector, int blockRowIndex, int blockColIndex){
    int count = 0;
    int blockWidthHeight = pow(N, 0.5);
//we need to find out which block to look in based on the coordinates we are given
    int blockRowStart = blockRowIndex - (blockRowIndex + blockWidthHeight) % blockWidthHeight;
    int blockColStart = blockColIndex - (blockColIndex + blockWidthHeight) % blockWidthHeight;

//once we found the specified block then we can search if the value exists the block
    for(int row = 0; row < blockWidthHeight; row++){
        for (int col = 0; col < blockWidthHeight; col++){
            if(inputVector[blockRowStart + row][blockColStart + col] == EMPTY)
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

vector<Test> findEmptyCellsLocation(vector<vector<int>> &inputVector) {
    vector<Test> emptyCellsLocationVector;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (inputVector[row][col] == EMPTY) {
                emptyCellsLocationVector.push_back({row, col, EMPTY});
            }
        }
    }
    return emptyCellsLocationVector;
}


// this function sums the relevant row col and block ranks for a specific cell
int RankOfCell(vector<vector<int>> &inputVector, int rowIndex, int colIndex){
    int rowRank = numberOfUnknownsInRow(inputVector, rowIndex);
    int colRank = numberOfUnknownsInCol(inputVector, colIndex);
    int blockRank = numberOfUnknownsInBlock(inputVector, rowIndex, colIndex);
    int cellRank = rowRank + colRank + blockRank;
    return cellRank;
}

//    but i only need to do this for the cells with zeros in it
//        and i need to set the rest of the matrix to null values
// this function has the ranks of all the unassigned values amongst zeros in a 2D array
vector<vector<Test>> rankSudoku(vector<vector<int>> &inputVector){
//    here im initialising the array with zero values
    vector<vector<Test>> rankSudokuVector (9,vector<Test>(9));
    for(int i = 0; i < rankSudokuVector.size(); ++i){
        for(int j = 0; j < rankSudokuVector[i].size(); ++j){
            rankSudokuVector[i][j].numberValue = 0;
        }
    }

// now to replace the zero values with the ranks
    vector<Test> emptyCellsLocationVector;
    emptyCellsLocationVector = findEmptyCellsLocation(inputVector);
    for(int i = 0; i < emptyCellsLocationVector.size(); i++){
        Test unassignedRank = emptyCellsLocationVector[i];
        rankSudokuVector[unassignedRank.rowCoordinate][unassignedRank.colCoordinate].rowCoordinate \
        = unassignedRank.rowCoordinate;
        rankSudokuVector[unassignedRank.rowCoordinate][unassignedRank.colCoordinate].colCoordinate \
        = unassignedRank.colCoordinate;
        rankSudokuVector[unassignedRank.rowCoordinate][unassignedRank.colCoordinate].numberValue \
        = RankOfCell(inputVector, unassignedRank.rowCoordinate, unassignedRank.colCoordinate);
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
vector<int> candidateInRow(vector<vector<int>> &inputVector, int RowIndex){

    unordered_set<int> s;
    vector<int> candidateVect;
    for(int i = 0; i< N; i++){
        s.insert(inputVector[RowIndex][i]);
    }

    for(int x = 1; x < N+1; x++){
        if(s.find(x) == s.end()){
            candidateVect.push_back(x);
        }
    }
    return candidateVect;
}

vector<int> candidateInCol(vector<vector<int>> &inputVector, int ColIndex){

    unordered_set<int> s;
    vector<int> candidateVect;
    for(int i = 0; i< N; i++){
        s.insert(inputVector[i][ColIndex]);
    }

    for(int x = 1; x < N+1; x++){
        if(s.find(x) == s.end()){
            candidateVect.push_back(x);
        }
    }
    return candidateVect;
}

vector<int> candidateInBlock(vector<vector<int>> &inputVector, int blockRowIndex, int blockColIndex){
    unordered_set<int> s;
    vector<int> candidateVect;

    int blockWidthHeight = pow(N, 0.5);
//we need to find out which block to look in based on the coordinates we are given
    int blockRowStart = blockRowIndex - (blockRowIndex + blockWidthHeight) % blockWidthHeight;
    int blockColStart = blockColIndex - (blockColIndex + blockWidthHeight) % blockWidthHeight;

//once we found the specified block then we can search if the value exists the block
    for(int row = 0; row < blockWidthHeight; row++){
        for (int col = 0; col < blockWidthHeight; col++){
            s.insert(inputVector[blockRowStart + row][blockColStart + col]);
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
vector<int> candidateInCell(vector<vector<int>> &inputVector, int RowIndex, int ColIndex){
    vector<int> rowCandidates = candidateInRow(inputVector, RowIndex);
    vector<int> colCandidates = candidateInCol(inputVector, ColIndex);
    vector<int> blockCandidates = candidateInBlock(inputVector, RowIndex, ColIndex);

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
vector<T> popFrontIntVector(vector<T>& vec)    {
    if(!vec.empty()){
        vec.erase(vec.begin());
        return vec;
    }
}

vector<vector<int>> updatedInputVector(vector<vector<int>> &inputVector, int RowIndex, int ColIndex, int value){
        inputVector[RowIndex][ColIndex] = value;
        return inputVector;
}

vector<vector<int>> erasedInputVector(vector<vector<int>> &inputVector, int RowIndex, int ColIndex){
    inputVector[RowIndex][ColIndex] = 0;
    return inputVector;
}

bool solve(vector<vector<int>> &inputVector){

//    im initialising the stack here
    MyStackV mySudokuStack;
    vector<vector<Test>> mySudokuRank (N,vector<Test>(N));

// so when the grid is not already solved, the continue to search and find values
// this is the number of empty cells in the sudoku
    int numberOfEmptyCells = findEmptyCellsLocation(inputVector).size();
    if(numberOfEmptyCells == 0){
        return true;
    }
    else{
//      Initialising the Rank Grid
        mySudokuRank = rankSudoku(inputVector);
        int currentDepth = 0;
//         while (currentDepth < numberOfEmptyCells){
        while (currentDepth < 26){
           // code that is used to move up the stack
           currentDepth = currentDepth + 1;


            // find the next best location (i didnt update the rank)
            Test bestCellChoice = bestCell(mySudokuRank);
            int bestCellChoiceRow = bestCellChoice.rowCoordinate;
            int bestCellChoiceCol = bestCellChoice.colCoordinate;

            // eg x:3 y:5
            // find the candidates
            // eg [4,5,6]
//            initialising the vector of candidates for the best cell
            vector<int> candidatesForBestCell = candidateInCell(inputVector, bestCellChoiceRow, bestCellChoiceCol);

            // if there are no candidates (made a mess)
            if(candidatesForBestCell.empty()){
                if(mySudokuStack.empty()){
                    return false;
                }
                // backtrack by popping off the stack (make sure stack is not empty otherwise no solution (break))
                // once pop off stack, x and y change - this is the one that is one that we can peek on the stack

                Test current;
                Test* topOfStack;
                topOfStack = &mySudokuStack.peek();
                current.rowCoordinate = topOfStack->rowCoordinate;
                current.colCoordinate = topOfStack->colCoordinate;
                current.numberValue = topOfStack->numberValue;
                mySudokuStack.pop();
//                once i popped off the stack, i need to remove that number from the input vector
                inputVector = erasedInputVector(inputVector, current.rowCoordinate, current.colCoordinate);
                // look for all candidates for it [4,5,6], where the candidate is not the value from peek which is 4 hence \
                // we use the next value which is 5 and add it to the stack after pop front
                Test currentCellChoice = bestCell(mySudokuRank);
                int currentCellChoiceRow = current.rowCoordinate;
                int currentCellChoiceCol = current.colCoordinate;
                vector<int> candidatesForCurrentCell = candidateInCell(inputVector, currentCellChoiceRow, currentCellChoiceCol);
                vector<int> popCandidatesForCurrentCell = popFrontIntVector(candidatesForCurrentCell);
                for(int i = 0; i < candidatesForCurrentCell.size()-1; i++){
                    candidatesForCurrentCell[i] = popCandidatesForCurrentCell[i];
                }
//                its not updating the input array by reference
                inputVector = updatedInputVector(inputVector, currentCellChoiceRow, currentCellChoiceCol,\
                candidatesForCurrentCell[0]);
                mySudokuRank = rankSudoku(inputVector);
//                inputVector[currentCellChoiceRow][currentCellChoiceCol] = candidatesForCurrentCell[0];
                mySudokuStack.push(currentCellChoiceRow, currentCellChoiceCol, candidatesForCurrentCell[0]);
                // increment currentDepth
                currentDepth += 1;
            }
            else{
                // else (happy path)
                // set the value in the main array of 4
                inputVector = updatedInputVector(inputVector, bestCellChoiceRow,\
                bestCellChoiceCol, candidatesForBestCell[0]);
                mySudokuRank = rankSudoku(inputVector);
//                inputVector[bestCellChoiceRow][bestCellChoiceCol] = candidatesForBestCell[0];
                // increment current depth
                currentDepth += 1;
                // add to stack [3,5,4]
                mySudokuStack.push(bestCellChoiceRow, bestCellChoiceCol, candidatesForBestCell[0]);
            }

        }
//    for(int emptyCellIterator = 0; emptyCellIterator < numberOfEmptyCells; emptyCellIterator++){
//            Test bestCellChoice = bestCell(mySudokuRank);
//            int bestCellChoiceRow = bestCellChoice.rowCoordinate;
//            int bestCellChoiceCol = bestCellChoice.colCoordinate;
////            initialising the vector of candidates for the best cell
//            vector<int> candidatesForBestCell = candidateInCell(inputArray, bestCellChoiceRow, bestCellChoiceCol);
//
////          now to change the value to the first candidate
//            inputArray[bestCellChoiceRow][bestCellChoiceCol] = candidatesForBestCell.front();
//
////          add this value and its index to the stack
//            mySudokuStack.push(bestCellChoiceRow, bestCellChoiceCol, candidatesForBestCell.front());
//
////          now to update rank grid and the best cell choice so i can move to next cell
//            mySudokuRank = rankSudoku(inputArray);
//            Test bestCellChoice2 = bestCell(mySudokuRank);
//            int bestCellChoiceRow2 = bestCellChoice2.rowCoordinate;
//            int bestCellChoiceCol2 = bestCellChoice2.colCoordinate;
////            initialising the vector of candidates for the best cell
//            vector<int> candidatesForBestCell2 = \
//                    candidateInCell(inputArray, bestCellChoiceRow2, bestCellChoiceCol2);
////            if i placed the wrong candidate choice in the cell and i need to backtrack
////          i think its the wrong choice if the next cell has no candidates
////          (but there would also be no candidates in the case where the grid is full)
//            if(candidatesForBestCell2.empty()){
//                mySudokuStack.pop();
////                to pop_front the first element in the candidate vector of the fist element we inserted
//                for(int i = 0; i < candidatesForBestCell.size() - 1; i++){
//                    candidatesForBestCell[i] = popFrontIntVector(candidatesForBestCell)[i];
//                }
////                retry with the next candidate in the list
//                inputArray[bestCellChoiceRow][bestCellChoiceCol] = candidatesForBestCell.front();
//
//            }
//            else{
//                continue;
//            }
//        }
//
//        return false;
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
//    printArray(inputArray);

    vector<vector<int>> inputVector(N, vector<int>(N, 0));
    inputVector = ArrayToVector(inputArray);

    cout << "testing input vector" << endl;
    printVector(inputVector);
    cout << endl;
    cout << endl;
    cout << endl;


    cout << "row, col 8 and block" << endl;
    cout << numberOfUnknownsInRow(inputVector, 8) << endl;
    cout << numberOfUnknownsInCol(inputVector, 8) << endl;
    cout << "block 9" << endl;
    cout << numberOfUnknownsInBlock(inputVector, 7, 7) << endl;

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
    emptyCellVect = findEmptyCellsLocation(inputVector);
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
    CandidateRVector = candidateInRow(inputVector, 1);
    for(int i = 0; i < CandidateRVector.size(); ++i) {
        cout << CandidateRVector[i] << " ";
    }
    cout << endl;

    cout << "col candidates in col 7 - index 6" << endl;
    CandidateCVector = candidateInCol(inputVector, 6);
    for(int i = 0; i < CandidateCVector.size(); ++i) {
        cout << CandidateCVector[i] << " ";
    }
    cout << endl;

    cout << "block candidates in block 3" << endl;
    CandidateBVector = candidateInBlock(inputVector, 1, 6);
    for(int i = 0; i < CandidateBVector.size(); ++i) {
        cout << CandidateBVector[i] << " ";
    }
    cout << endl;
    cout << "candidates in cell [1][6]" << endl;
    CandidateCellVector = candidateInCell(inputVector, 1, 6);
    for(int i = 0; i < CandidateCellVector.size(); ++i) {
        cout << CandidateCellVector[i] << " ";
    }
    cout << endl;
    cout << "-------------" << endl;
    cout << "checking pop_front" << endl;
    vector<int> popCandidateVect;
    popCandidateVect = popFrontIntVector(CandidateCellVector);
    for(int i = 0; i< popCandidateVect.size(); i++){
        cout << popCandidateVect[i] << endl;
    }
    cout << endl;
    cout << "-------------" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "this is printing the rank 2D Array" << endl;
    cout << "asdf" << endl;
    vector<vector<Test>> mySudokuRank (9,vector<Test>(9));
    mySudokuRank = rankSudoku(inputVector);

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
    bestCellAndValue = bestCell(rankSudoku(inputVector));
    cout << bestCellAndValue.rowCoordinate << " " << bestCellAndValue.colCoordinate << " " << \
    bestCellAndValue.numberValue << endl;

    cout << "________________________" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "testing the solve function 3 times" << endl;
    if(solve(inputVector)) {
        cout << "yay!" << endl;
    }

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