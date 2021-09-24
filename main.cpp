#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <fstream>
#include <stack>
#include <cmath>
#include "mysudoku.h"

using namespace std;

int main() {

//    vector<Test> idkanymore;
//    int a = 0;
//    int b = 2;
//    int c = 3;
//    idkanymore.push_back({a, b, c});
//    idkanymore.push_back({a, b, c});
//    idkanymore.push_back({a, b, c});
//    idkanymore.push_back({a, b, c});
//    idkanymore.push_back({a, b, c});
//    idkanymore.push_back({a, b, c});
//
//    for(int i = 0; i < idkanymore.size(); i++){
//        cout << idkanymore[i].rowCoordinate << ", " << idkanymore[i].colCoordinate
//             << ", " << idkanymore[i].numberValue << endl;
//    }

//    vector<vector<int>> multiplication (10,vector<int>(10));
//    for(int i{0}; i<multiplication.size(); ++i){
//        for(int j{0}; j<multiplication[i].size(); ++j){
//            multiplication[i][j] = 0;
//        }
//    }
//
//    for(int i{1}; i < multiplication.size(); ++i){
//        for(int j{1}; j < multiplication[i].size(); ++j){
//            std::cout<<multiplication[i][j]<<"\t";
//        }
//        printf("\n");
//    }

    vector<vector<Test>> mySudokuRankRow (9,vector<Test>(9));
    for(int i = 0; i<mySudokuRankRow.size(); ++i){
        for(int j = 0; j<mySudokuRankRow[i].size(); ++j){
            mySudokuRankRow[i][j].numberValue = 0;
        }
    }

    for(int i = 0; i < mySudokuRankRow.size(); ++i){
        for(int j = 0; j < mySudokuRankRow[i].size(); ++j){
            std::cout<< mySudokuRankRow[i][j].numberValue <<"\t";
        }
        printf("\n");
    }


    return 0;
}
