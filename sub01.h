
#ifndef SUDOKU_SUB01_H
#define SUDOKU_SUB01_H

void fillArray(int inputArray[ROWS][COLUMNS]);
void printArray(int Array[ROWS][COLUMNS]);
bool used_in_row(int Array[N][N], int row, int value);
bool used_in_block(int Array[N][N], int blockRowIndex, int blockColIndex, int value);
bool isSafeCell(int Array[N][N],int RowIndex,int ColIndex, int value);
int* ptrNumberOfUnknownsRows(int Array[N][N]);

#endif //SUDOKU_SUB01_H
