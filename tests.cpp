#define CATCH_CONFIG_MAIN




#include <iostream>
#include "catch.hpp"
#include "mysudoku.h"
#include "sub01.h"



using namespace std;

//void fillArray(int inputArray[ROWS][COLUMNS]){
//    for(int i = 0; i < ROWS; i ++){
//        for(int j = 0 ; j < COLUMNS; j++){
//            cin >> inputArray[i][j];
//        }
//    }
//}
//
//void printArray(int Array[ROWS][COLUMNS]){
//    for(int i =0; i < ROWS; i++){
//        for(int j=0; j < COLUMNS; j++){
//            cout << Array[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//int* ptrNumberOfUnknownsRows(int Array[N][N]){
//    int* arrayWithUnknowns = new int[N];
//    for(int row = 0; row < N; row++){
//        int count = 0;
//        for(int col = 0; col < N; col++){
//            if(Array[row][col] == EMPTY){
//                count += 1;
//            }
//        }
//        arrayWithUnknowns[row] = count;
//    }
//    return arrayWithUnknowns;
//}

TEST_CASE( "stupid/1=2", "[classics]" ){
    int one = 1;
    REQUIRE( one == 2 );
}

TEST_CASE("testing if the count of unknowns work", "[classics]"){
    int TestArrayOfUnknownCount[9];

    int inputArray[9][9];
    fillArray(inputArray);
    printArray(inputArray);
    for(int i = 0; i < 9; i++){
        int count = 0;
        for(int j = 0; j < 9; j ++){
            if(inputArray[i][j] == 0){
              count += 1;
            }
        }
        TestArrayOfUnknownCount[i] = count;
    }
    int* pointerToArray = ptrNumberOfUnknownsRows(inputArray);
    REQUIRE(TestArrayOfUnknownCount[0] == pointerToArray[0]);
}




//int main(){
//    this is just to get the inputs into an array and print the input array out
//    int inputArray[ROWS][COLUMNS];
//    fillArray(inputArray);
//    printArray(inputArray);
//
//    this is to test if the count of unknowns in the row is working
//
//
//
//
//    int TestArrayOfUnknownCount[N];
//
//
//
//    return 0;
//}

