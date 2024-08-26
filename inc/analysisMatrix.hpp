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

    // Helper functions to get prime and inverted rows
    void getPrimeRow(short num, std::vector<short> &rowVec) const;
    void getInvertedRow(short num, std::vector<short> &rowVec) const;

    public :
        // Constructors
    AnalysisMatrix() = delete;
    AnalysisMatrix(std::vector<short> P0);
    AnalysisMatrix(const AnalysisMatrix &other) = delete;
    ~AnalysisMatrix() = default;

    /**
     * @brief Get the Row object associated with the Row type and number
     * 
     * @param row Row number and type to get
     * @return std::vector<short>. Vector with all the numbers 1-12 arranged correctly
     */
    std::vector<short> getRow(Row row) const;

    // Row and column maps to find rows of the matrix fast. Used in testing
    std::vector<size_t> getRowMap() const;
    std::vector<size_t> getColMap() const;

    void printMatrix(std::ostream& os) const;
};

// Helper Printing functions
std::ostream &operator<<(std::ostream &os, const AnalysisMatrix &a);

std::ostream &operator<<(std::ostream &os, const Row &r);

#endif