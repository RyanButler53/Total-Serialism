#include "matrix.hpp"
#include <iostream>
template <typename T>
Matrix<T>::Matrix(size_t numRows, size_t numCols): numRows_{numRows}, numCols_{numCols}
{
    size_t numEntries = numRows * numCols;
    data_ = new T[numEntries];
}

template <typename T>
Matrix<T>::~Matrix()
{
    delete[] data_;
}

template <typename T>
T& Matrix<T>::operator() (size_t row, size_t col) const {
    size_t idx = row * numCols_ + col;
    return data_[idx];
}

template <typename T>
void Matrix<T>::print(std::ostream& os) const {
    for (size_t r = 0; r < numRows_; ++r)
    {
        for (size_t c = 0; c < numCols_; ++c)
        {
            size_t idx = r * numCols_ + c;

            os <<  data_[idx]<< " ";
        }
        os << std::endl;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m){
    m.print(os);
    return os;
}
