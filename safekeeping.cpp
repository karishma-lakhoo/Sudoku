

//    MyStackV asdfasdf;
//    vector<Test> pasta;
//    int rowCoord = 0;
//    int colCoord = 0;
//    int numVal = 0;
//    pasta.push_back({rowCoord, colCoord, numVal});
//
//    asdfasdf.push(asddf);

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


//
//
//int* ptrNumberOfUnknownsCols(int Array[N][N]){
//    int* arrayWithUnknowns = new int[N];
//    for(int col = 0; col < N; col++){
//        int count = 0;
//        for(int row = 0; row < N; row++){
//            if(Array[row][col] == EMPTY){
//                count += 1;
//            }
//        }
//        arrayWithUnknowns[col] = count;
//    }
//    return arrayWithUnknowns;
//}
//
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
//
//
//
//
//
//int* ptrNumberOfUnknownsBlock(int Array[N][N]) {
//    int *arrayWithUnknowns = new int[N];
//    int blockWidthHeight = pow(N, 0.5);
//    for (int i = 0; i < 0; i++) {
//        int count = 0;
//        int blockRowStart = i - (i + blockWidthHeight) % blockWidthHeight;
//        int blockColStart = i - (i + blockWidthHeight) % blockWidthHeight;
//        for (int row = 0; row < blockWidthHeight; row++) {
//            for (int col = 0; col < blockWidthHeight; col++) {
//                if (Array[blockRowStart + row][blockColStart + col] == 0) {
//                    count += 1;
//                }
//            }
//            arrayWithUnknowns[i] = count;
//        }
//    }
//    return arrayWithUnknowns;
//}


//int** rankSudoku(int Array[N][N]){
////    here im initialising the array with NaN values
//    int **rankSudokuArray = new int* [N];
//    for(int i = 0; i < N; i++){
//        rankSudokuArray[i] = new int[N];
//        for (int j = 0; j < N; ++j) {
//            rankSudokuArray[i][j] = 0;
//        }
//    }
//// now to replace the zero values with the ranks
//    vector<Test> emptyCellsLocationVector;
//    emptyCellsLocationVector = findEmptyCellsLocation(Array);
//    for(int i = 0; i < emptyCellsLocationVector.size(); i++){
//        rankSudokuArray[emptyCellsLocationVector[i].rowCoordinate][emptyCellsLocationVector[i].colCoordinate] \
//        = RankOfCell(Array, emptyCellsLocationVector[i].rowCoordinate, emptyCellsLocationVector[i].colCoordinate);
//    }
//    return rankSudokuArray;
//}