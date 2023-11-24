#include <iostream>
#include "analysisMatrix.hpp"
#include <chrono>

using namespace std;

template<typename T>
void printVec(vector<T>& vec){
    for (auto& e: vec){
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    cout << "Analysis Matrix Tests" << endl;

    std::vector<short> row{9, 6, 7, 3, 4, 0, 1, 10, 11, 2, 5, 8};
    AnalysisMatrix A = AnalysisMatrix(row);
    std::vector<size_t> rowMap = A.getRowMap();
    std::vector<size_t> colMap = A.getColMap();

    vector<size_t> testMapRow = vector<size_t>{0,9,10,6,7,3,4,1,2,5,8,11};
    vector<size_t> testColMap = vector<size_t>{0,3,2,6,5,9,8,11,10,7,4,1};

    assert(testMapRow == rowMap);
    assert(testColMap == colMap);

    cout << A << endl;

    vector<short> row1 = A.getRow(Row{RowType(R), 5});
    vector<short> row2 = A.getRow(Row{RowType(P), 2});
    vector<short> row3 = A.getRow(Row{RowType(I), 5});
    vector<short> row4 = A.getRow(Row{RowType(P), 11});
    vector<short> row5 = A.getRow(Row{RowType(RI), 0});
    vector<short> row6 = A.getRow(Row{RowType(RI), 7});

    vector<short> row1_test = vector<short>{1,10,7,4,3,6,5,9,8,0,11,2};
    vector<short> row2_test = vector<short>{11,8,9,5,6,2,3,0,1,4,7,10};
    vector<short> row3_test = vector<short>{2,5,4,8,7,11,10,1,0,9,6,3};
    vector<short> row4_test = vector<short>{8,5,6,2,3,11,0,9,10,1,4,7};
    vector<short> row5_test = vector<short>{10,1,4,7,8,5,6,2,3,11,0,9};
    vector<short> row6_test = vector<short>{5,8,11,2,3,0,1,9,10,6,7,4};

    assert(row1 == row1_test);
    assert(row2 == row2_test);
    assert(row3 == row3_test);
    assert(row4 == row4_test);
    assert(row5 == row5_test);
    assert(row6 == row6_test);

    cout << "All tests pass" << endl;
    return 0;
}