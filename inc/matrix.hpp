// Template for a matrix class. 
#include <ostream>

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

template <typename T>
class Matrix {
    
  private:
    T* data_;
    size_t numRows_;
    size_t numCols_;

  public:
    Matrix(size_t numRows, size_t numColumns);
    Matrix(const Matrix &other) = default;
    ~Matrix();

    T &operator()(size_t row, size_t col) const;
    void print(std::ostream &os) const;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m);

#include "matrix-private.hpp"

#endif // MATRIX_HPP_INCLUDED