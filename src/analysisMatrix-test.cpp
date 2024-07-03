#include <iostream>
#include "analysisMatrix.hpp"
#include <gtest/gtest.h>
#include <chrono>

using namespace std;


TEST(AnalysisMatrixTest, Maps){
    AnalysisMatrix A{{9, 6, 7, 3, 4, 0, 1, 10, 11, 2, 5, 8}};

    vector<size_t> rowMap = A.getRowMap();
    vector<size_t> colMap = A.getColMap();

    vector<size_t> testMapRow = vector<size_t>{0,9,10,6,7,3,4,1,2,5,8,11};
    vector<size_t> testMapCol = vector<size_t>{0,3,2,6,5,9,8,11,10,7,4,1};

    ASSERT_EQ(rowMap, testMapRow);
    ASSERT_EQ(colMap, testMapCol);
}

TEST(AnalysisMatrixTest, getRow){

    AnalysisMatrix A{{9, 6, 7, 3, 4, 0, 1, 10, 11, 2, 5, 8}};

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

    ASSERT_EQ(row1_test, row1);
    ASSERT_EQ(row2_test, row2);
    ASSERT_EQ(row3_test, row3);
    ASSERT_EQ(row4_test, row4);
    ASSERT_EQ(row5_test, row5);
    ASSERT_EQ(row6_test, row6);

}
