
#ifndef SUDOKU_9X9_SUDOKU_SOLVER_H
#define SUDOKU_9X9_SUDOKU_SOLVER_H

void fillArray(int inputArray[ROWS][COLUMNS]);
void printArray(int Array[ROWS][COLUMNS]);
bool used_in_row(int Array[N][N], int row, int value);
bool used_in_block(int Array[N][N], int blockRowIndex, int blockColIndex, int value);
bool isSafeCell(int Array[N][N],int RowIndex,int ColIndex, int value);
int* ptrNumberOfUnknownsRows(int Array[N][N]);

#endif //SUDOKU_9X9_SUDOKU_SOLVER_H
