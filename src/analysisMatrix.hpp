#include "matrix.hpp"
#include <vector>
#include <ostream>

#ifndef ANALYSIS_MATRIX_HPP_INCLUDED
#define ANALYSIS_MATRIX_HPP_INCLUDED

const int ROW_LEN = 12;

enum RowType
{
    P = 0, // Prime
    I = 1, // Inverted
    R = 2, // Retrograde
    RI = 3 // Retrograde Inverted
};

struct Row
{
    RowType rtype_;
    short num_;

    Row() = default;
    Row(RowType rtype, short num);
};

class AnalysisMatrix
{
private:
    Matrix<short> matrix_;
    std::vector<size_t> rowToIndex_;
    std::vector<size_t> colToIndex_;
    std::vector<short> P0_;
    std::vector<short> I0_;

    public :
        // Constructors
    AnalysisMatrix() = delete;
    AnalysisMatrix(std::vector<short> P0);
    AnalysisMatrix(const AnalysisMatrix &other) = delete;
    ~AnalysisMatrix() = default;

    // Get Data members
    void getPrimeRow(short num, std::vector<short> &rowVec) const;
    void getInvertedRow(short num, std::vector<short> &rowVec) const;

    std::vector<short> getRow(Row row) const;
    std::vector<size_t> getRowMap() const;
    std::vector<size_t> getColMap() const;
    void printMatrix(std::ostream& os) const;
};

std::ostream &operator<<(std::ostream &os, const AnalysisMatrix &a);

std::ostream &operator<<(std::ostream &os, const Row &r);

#endif