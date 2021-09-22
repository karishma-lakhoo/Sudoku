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

    vector<Test> idkanymore;
    int a = 0;
    int b = 2;
    int c = 3;
    idkanymore.push_back({a, b, c});
    idkanymore.push_back({a, b, c});
    idkanymore.push_back({a, b, c});
    idkanymore.push_back({a, b, c});
    idkanymore.push_back({a, b, c});
    idkanymore.push_back({a, b, c});

    for(int i = 0; i < idkanymore.size(); i++){
        cout << idkanymore[i].x << ", " << idkanymore[i].y
             << ", " << idkanymore[i].z << endl;
    }


    return 0;
}
