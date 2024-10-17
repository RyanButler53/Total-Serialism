#include <iostream>
#include "analysisMatrix.hpp"

using namespace std;

AnalysisMatrix::AnalysisMatrix(vector<short> P0):
    matrix_{Matrix<short>(ROW_LEN, ROW_LEN)},P0_{P0}
{
    std::copy(P0.begin(), P0.end(), &(matrix_(0,0)));
    for (size_t row = 1; row < ROW_LEN; ++row){
        short offset = (P0[0] - P0[row]);
        for (size_t col = 0; col < ROW_LEN; ++col){
            matrix_(row, col) = (P0[col] + offset + ROW_LEN) % 12;
        }
    }
    for (short& entry : P0){
        rowToIndex_.push_back((entry  + ROW_LEN- P0[0]) % ROW_LEN);
        colToIndex_.push_back((P0[0] + ROW_LEN - entry) % ROW_LEN);
    }
    for (size_t r = 0; r < ROW_LEN; ++r){
        I0_.push_back(matrix_(r, 0));
    }
}

vector<size_t> AnalysisMatrix::getRowMap() const{
    return rowToIndex_;
}

vector<size_t> AnalysisMatrix::getColMap() const{
    return colToIndex_;
}

void AnalysisMatrix::printMatrix(ostream& os) const {
    os << matrix_ << "\n";
    for (size_t s : colToIndex_){
        cout << "P" << s << " ";
    }
    cout << endl;
    for (size_t s : rowToIndex_){
        cout << "I" << s << " ";
    }
    cout << endl;
    cout << "P-0: ";
    for (size_t s : P0_)
    {
        cout << s << " ";
    }
    cout << endl;
    cout << "I-0: ";
    for (size_t s : I0_){
        cout  << s << " ";
    }
    cout << endl; 
}

void AnalysisMatrix::getPrimeRow(short num, vector<short>& row) const{
    for (auto& p : P0_){
        row.push_back((p + num) % 12);
    }
}

void AnalysisMatrix::getInvertedRow(short num, vector<short>& row) const{
    for (auto& p : I0_){
        row.push_back((p + num) % 12);
    }
}

vector<short> AnalysisMatrix::getRow(Row row) const{

     // Check if valid row num
    short num = row.num_;
    RowType rtype = row.rtype_;
    vector<short> rowValues;
    if (rtype == RowType(P)) {
         getPrimeRow(num, rowValues);
    } else if (rtype == RowType(R)) {
        getPrimeRow(num, rowValues);
        std::reverse(rowValues.begin(), rowValues.end());
    } else if (rtype == RowType(I)) {
        getInvertedRow(num, rowValues);
    } else {
        getInvertedRow(num, rowValues);
        std::reverse(rowValues.begin(), rowValues.end());
    }
    return rowValues;
}

Row::Row(RowType rtype,short num):rtype_{rtype}, num_{num} {
    if (num_ < 0){
        num_ += ROW_LEN;
    } else if (num_ > 11) {
        num_ = num_ % ROW_LEN;
    }
}

ostream &operator<<(ostream &os, const AnalysisMatrix &a){
    a.printMatrix(os);
    return os;
}

ostream &operator<<(ostream &os, const Row& r){
    os << r.rtype_ << "-" << r.num_;
    return os;
}