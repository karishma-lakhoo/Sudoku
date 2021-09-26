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


vector<vector<int>> ArrayToVectorTemp(int inputArray[ROWS][COLUMNS]){
    vector<vector<int>> inputVector(N, vector<int> (N, 0));
    inputVector[0][0] = 0 ;
    inputVector[1][0] = 0 ;
    inputVector[2][0] = 0 ;
    inputVector[3][0] = 0 ;
    inputVector[4][0] = 0 ;
    inputVector[5][0] = 0 ;
    inputVector[6][0] = 3 ;
    inputVector[7][0] = 5 ;
    inputVector[8][0] = 9 ;
    inputVector[0][1] = 4 ;
    inputVector[1][1] = 0 ;
    inputVector[2][1] = 0 ;
    inputVector[3][1] = 8 ;
    inputVector[4][1] = 5 ;
    inputVector[5][1] = 1 ;
    inputVector[6][1] = 0 ;
    inputVector[7][1] = 7 ;
    inputVector[8][1] = 2 ;
    inputVector[0][2] = 0 ;
    inputVector[1][2] = 2 ;
    inputVector[2][2] = 6 ;
    inputVector[3][2] = 0 ;
    inputVector[4][2] = 0 ;
    inputVector[5][2] = 9 ;
    inputVector[6][2] = 0 ;
    inputVector[7][2] = 0 ;
    inputVector[8][2] = 8 ;
    inputVector[0][3] = 0 ;
    inputVector[1][3] = 0 ;
    inputVector[2][3] = 0 ;
    inputVector[3][3] = 0 ;
    inputVector[4][3] = 0 ;
    inputVector[5][3] = 0 ;
    inputVector[6][3] = 4 ;
    inputVector[7][3] = 1 ;
    inputVector[8][3] = 0 ;
    inputVector[0][4] = 0 ;
    inputVector[1][4] = 0 ;
    inputVector[2][4] = 0 ;
    inputVector[3][4] = 7 ;
    inputVector[4][4] = 9 ;
    inputVector[5][4] = 6 ;
    inputVector[6][4] = 0 ;
    inputVector[7][4] = 0 ;
    inputVector[8][4] = 0 ;
    inputVector[0][5] = 0 ;
    inputVector[1][5] = 8 ;
    inputVector[2][5] = 5 ;
    inputVector[3][5] = 0 ;
    inputVector[4][5] = 0 ;
    inputVector[5][5] = 0 ;
    inputVector[6][5] = 0 ;
    inputVector[7][5] = 0 ;
    inputVector[8][5] = 0 ;
    inputVector[0][6] = 1 ;
    inputVector[1][6] = 0 ;
    inputVector[2][6] = 0 ;
    inputVector[3][6] = 9 ;
    inputVector[4][6] = 0 ;
    inputVector[5][6] = 0 ;
    inputVector[6][6] = 7 ;
    inputVector[7][6] = 2 ;
    inputVector[8][6] = 0 ;
    inputVector[0][7] = 7 ;
    inputVector[1][7] = 5 ;
    inputVector[2][7] = 0 ;
    inputVector[3][7] = 1 ;
    inputVector[4][7] = 3 ;
    inputVector[5][7] = 4 ;
    inputVector[6][7] = 0 ;
    inputVector[7][7] = 0 ;
    inputVector[8][7] = 6 ;
    inputVector[0][8] = 9 ;
    inputVector[1][8] = 4 ;
    inputVector[2][8] = 8 ;
    inputVector[3][8] = 0 ;
    inputVector[4][8] = 0 ;
    inputVector[5][8] = 0 ;
    inputVector[6][8] = 0 ;
    inputVector[7][8] = 0 ;
    inputVector[8][8] = 0 ;


    return inputVector;
}
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
vector<vector<Test>> rankSudoku(vector<vector<int>> &inputVector) {
//    here im initialising the array with zero values
    vector<vector<Test>> rankSudokuVector(9, vector<Test>(9));
    for (int i = 0; i < rankSudokuVector.size(); ++i) {
        for (int j = 0; j < rankSudokuVector[i].size(); ++j) {
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
Test bestCell(vector<vector<Test>> &rankSudoku){
    Test t;

//    for(int row = 0; row < N; row++){
//        for (int col = 0; col < N; ++col) {
//            rowMinimums[col] = rankSudoku[i][j];
//            min.numberValue = *min_element()
//
//        }
//        result

//    but in the case where the rank[0][0] == 0 & then this associated number value is weird
//    so i need to recode this
//    int minElementIndex =

    if(rankSudoku[0][0].numberValue == 0){
        rankSudoku[0][0].numberValue = 10000;
    }

    t.numberValue = rankSudoku[0][0].numberValue;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(rankSudoku[i][j].numberValue != 0){
                if(rankSudoku[i][j].numberValue <= t.numberValue){
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

vector<int> updatedCandidatesVector(vector<int> &CandidateVector, Test current){

    vector<int> newVector ;

    if(CandidateVector.empty()){
        return CandidateVector;
    }
    else{
        for(int i = 0; i < CandidateVector.size(); i ++){
            if(CandidateVector[i] > current.numberValue){
                newVector.push_back(CandidateVector[i]);
            }
        }

    }

    return newVector;
}



bool solve(vector<vector<int>> &inputVector){

//    im initialising the stack here
    MyStackV mySudokuStack;
    vector<vector<Test>> mySudokuRank (N,vector<Test>(N));
    vector<vector<int>> mySudokuIntRank (N,vector<int>(N));
    vector<int> candidatesForBestCell;
    vector<int> candidatesForCurrentCell;
    Test current;
    Test bestCellChoice;
    int bestCellChoiceRow;
    int bestCellChoiceCol;
    int currentCellChoiceRow;
    int currentCellChoiceCol;
    Test* topOfStack;
    Test* topOfStack1;

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
        while (currentDepth < numberOfEmptyCells){
            mySudokuRank = rankSudoku(inputVector);

            // find the next best location (i didnt update the rank)
            bestCellChoice = bestCell(mySudokuRank);
//            vector<vector<int>> mySudokuIntRankX (N,vector<int>(N));

            bestCellChoiceRow = bestCellChoice.rowCoordinate;
            bestCellChoiceCol = bestCellChoice.colCoordinate;

            //  its breaking here because it returns an out of bounds row coordinate - so in that case, im setting the candidate mattrix to none
            candidatesForBestCell = candidateInCell(inputVector, bestCellChoiceRow, bestCellChoiceCol);

            cout << "bestcell r " << bestCellChoiceRow << " c " << bestCellChoiceCol << " cand ";
            for (int i=0; i<candidatesForBestCell.size(); i++){
                cout << candidatesForBestCell[i] << " ";
            }
            cout << "" << endl;

//          initialising the vector of candidates for the best cell

            // if there are no candidates (made a mess)
            if(candidatesForBestCell.empty()){
                cout << "not happy at all" << endl;
                if(mySudokuStack.empty()){
                    return false;
                }
                //  backtrack by popping off the stack (make sure stack is not empty otherwise no solution (break))
                // once pop off stack, x and y change - this is the one that is one that we can peek on the stack

                topOfStack = &mySudokuStack.peek();
                current.rowCoordinate = topOfStack->rowCoordinate;
                current.colCoordinate = topOfStack->colCoordinate;
                current.numberValue = topOfStack->numberValue;
                currentCellChoiceRow = current.rowCoordinate;
                currentCellChoiceCol = current.colCoordinate;
                mySudokuStack.pop();
                cout << "popped off the stack since the candidate vector was empty" << endl;
                inputVector = erasedInputVector(inputVector, currentCellChoiceRow, currentCellChoiceCol);

                candidatesForCurrentCell = candidateInCell(inputVector, currentCellChoiceRow, currentCellChoiceCol);
//                candidatesForCurrentCell = up
                cout << "candidates" << endl;
                for (int i = 0; i < candidatesForCurrentCell.size(); ++i) {
                    cout << candidatesForCurrentCell[i] << " ";
                }
                cout << endl;
                if (candidatesForCurrentCell.size() > 0) {
                    candidatesForCurrentCell = updatedCandidatesVector(candidatesForCurrentCell, current);
                }

                while(candidatesForCurrentCell.size() < 1){
                    cout << "____________________" << endl;
                    cout << " Went back - " << "current depth " <<currentDepth << endl;
                    topOfStack1 = &mySudokuStack.peek();
                    current.rowCoordinate = topOfStack1->rowCoordinate;
                    current.colCoordinate = topOfStack1->colCoordinate;
                    current.numberValue = topOfStack1->numberValue;
                    currentCellChoiceRow = current.rowCoordinate;
                    currentCellChoiceCol = current.colCoordinate;
                    cout << "row " << currentCellChoiceRow << " " << "col" << " " << currentCellChoiceCol << " " << current.numberValue << endl;
                    mySudokuStack.pop();
                    if(mySudokuStack.empty()){
                        return false;
                    }
                    currentDepth -=1;
                    inputVector = erasedInputVector(inputVector, currentCellChoiceRow, currentCellChoiceCol);
                    candidatesForCurrentCell = candidateInCell(inputVector, currentCellChoiceRow, currentCellChoiceCol);
                    candidatesForCurrentCell = updatedCandidatesVector(candidatesForCurrentCell, current);
                    if(candidatesForCurrentCell.size() >= 1){
                        cout << "elp" << endl;
                        for (int i = 0; i < candidatesForCurrentCell.size(); ++i) {
                            cout << candidatesForCurrentCell[i] << endl;
                        }
                        break;
                    }
                }


                mySudokuStack.push(currentCellChoiceRow, currentCellChoiceCol, candidatesForCurrentCell[0]);
                cout << "Added to sad stack r:" << currentCellChoiceRow << " c:" << currentCellChoiceCol \
                << " val:" << candidatesForCurrentCell[0] << endl;
//                currentDepth +=1;

                inputVector = updatedInputVector(inputVector, currentCellChoiceRow, currentCellChoiceCol,\
                candidatesForCurrentCell.front());

                mySudokuRank = rankSudoku(inputVector);

//                inputVector[currentCellChoiceRow][currentCellChoiceCol] = candidatesForCurrentCell[0];
//                mySudokuStack.push(currentCellChoiceRow, currentCellChoiceCol, candidatesForCurrentCell[0]);
                // increment currentDepth
            }
            else{
                // (happy path) :)
                // set the value in the main array of 4
                inputVector = updatedInputVector(inputVector, bestCellChoiceRow,\
                bestCellChoiceCol, candidatesForBestCell[0]);
                // start: calculate sudoku rank
                mySudokuRank = rankSudoku(inputVector);
                for(int i= 0; i< N; i++){
                    for(int j = 0; j < N; j++){
                        mySudokuIntRank[i][j] = mySudokuRank[i][j].numberValue;
                    }
                }
                // end: calculate sudoku rank
                currentDepth += 1;
                // add to stack [3,5,4]
                mySudokuStack.push(bestCellChoiceRow, bestCellChoiceCol, candidatesForBestCell[0]);
                cout << "Added to stack r:" << bestCellChoiceRow << " c:" << bestCellChoiceCol \
                << " val:" << candidatesForBestCell[0] << endl;
                inputVector = updatedInputVector(inputVector, bestCellChoiceRow, bestCellChoiceCol,\
                candidatesForBestCell[0]);

                mySudokuRank = rankSudoku(inputVector);
//                cout << endl;
//                printVector(mySudokuIntRank);
            }
            if(mySudokuStack.empty()){
                return false;
            }
            cout << "Counter: " << currentDepth << endl;
            cout << endl;

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
//    printArray(inputArray);

    vector<vector<int>> inputVector(N, vector<int>(N, 0));
    //inputVector = ArrayToVector(inputArray);
    inputVector = ArrayToVector(inputArray);
   // inputVector = ArrayToVectorTemp(inputArray);

//    cout << "testing input vector" << endl;
//    printVector(inputVector);
//    cout << endl;
//    cout << endl;
//    cout << endl;


//    cout << "row, col 8 and block" << endl;
//    cout << numberOfUnknownsInRow(inputVector, 8) << endl;
//    cout << numberOfUnknownsInCol(inputVector, 8) << endl;
//    cout << "block 9" << endl;
//    cout << numberOfUnknownsInBlock(inputVector, 7, 7) << endl;

//    cout << endl;
//    cout << "\this is just to test the empty cells location funciton" << endl;
//    vector<Test> emptyCellVect;
//    emptyCellVect = findEmptyCellsLocation(inputVector);
//    cout << emptyCellVect.size() << endl;
//    for(int i = 0; i < emptyCellVect.size(); i++){
//        cout << emptyCellVect[i].numberValue << " " << emptyCellVect[i].rowCoordinate << " " << emptyCellVect[i].colCoordinate << endl;
//    }
//    cout << endl;
//    cout << endl;
//    cout << endl;
    vector<int> CandidateRVector;
    vector<int> CandidateCVector;
    vector<int> CandidateBVector;
    vector<int> CandidateCellVector;
  //  cout << "row candidates in row 2 - index 1" << endl;
    CandidateRVector = candidateInRow(inputVector, 1);
//    for(int i = 0; i < CandidateRVector.size(); ++i) {
//        cout << CandidateRVector[i] << " ";
//    }
//    cout << endl;

 //   cout << "col candidates in col 7 - index 6" << endl;
//    CandidateCVector = candidateInCol(inputVector, 6);
//    for(int i = 0; i < CandidateCVector.size(); ++i) {
//        cout << CandidateCVector[i] << " ";
//    }
//    cout << endl;

//    cout << "block candidates in block 3" << endl;
//    CandidateBVector = candidateInBlock(inputVector, 1, 6);
//    for(int i = 0; i < CandidateBVector.size(); ++i) {
//        cout << CandidateBVector[i] << " ";
//    }
//    cout << endl;
//    cout << "candidates in cell [1][6]" << endl;
//    CandidateCellVector = candidateInCell(inputVector, 1, 6);
//    for(int i = 0; i < CandidateCellVector.size(); ++i) {
//        cout << CandidateCellVector[i] << " ";
//    }
//    cout << endl;
//    cout << "-------------" << endl;
//    cout << "checking pop_front" << endl;
//    vector<int> popCandidateVect;
//    popCandidateVect = popFrontIntVector(CandidateCellVector);
//    for(int i = 0; i< popCandidateVect.size(); i++){
//        cout << popCandidateVect[i] << endl;
//    }
//    cout << endl;
//    cout << "-------------" << endl;
//    cout << endl;
//    cout << endl;
//    cout << endl;
//    cout << "this is printing the rank 2D Array" << endl;
//    cout << "asdf" << endl;
//    vector<vector<Test>> mySudokuRank (9,vector<Test>(9));
//    mySudokuRank = rankSudoku(inputVector);
//
//    for(int i = 0; i < mySudokuRank.size(); ++i) {
//        for(int j = 0; j < mySudokuRank[i].size(); ++j) {
//            cout << mySudokuRank[i][j].numberValue << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    cout << "________________________" << endl;
//    cout << endl;
//    cout << "location of best cell and associated value" << endl;
//    Test bestCellAndValue;
//    bestCellAndValue = bestCell(mySudokuRank);
//    cout << bestCellAndValue.rowCoordinate << " " << bestCellAndValue.colCoordinate << " " << \
//    bestCellAndValue.numberValue << endl;
//
//    cout << "________________________" << endl;
//    cout << endl;
//    cout << endl;
//    cout << endl;
    cout << "testing the solve function" << endl;
    if(solve(inputVector)) {
        cout << "yay!" << endl;
        printVector(inputVector);
    }
    else {
        cout << "No Solution" << endl;
    }

    return 0;
}