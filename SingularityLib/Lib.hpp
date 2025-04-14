#ifndef SINGULARITYLIB_LIB_HPP
#define SINGULARITYLIB_LIB_HPP

#include "DenseStorage.hpp"
#include "Matrix.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp, size_t _rows, size_t _cols, StorageOrdr _st_ordr>
using DenseMatrix =
    Matrix<_Tp, _rows, _cols, StorageType::Dense, _st_ordr, DenseStorage>;

template <typename _Tp, size_t _rows, size_t _cols>
using DenseRowMatrix = Matrix<_Tp,
                              _rows,
                              _cols,
                              StorageType::Dense,
                              StorageOrdr::RowMajor,
                              DenseStorage>;

template <typename _Tp, size_t _rows, size_t _cols>
using DenseColMatrix = Matrix<_Tp,
                              _rows,
                              _cols,
                              StorageType::Dense,
                              StorageOrdr::ColMajor,
                              DenseStorage>;

template <typename _Tp, size_t _rows, size_t _cols>
using SprseMatrix = Matrix<_Tp,
                           _rows,
                           _cols,
                           StorageType::Sprse,
                           StorageOrdr::Udefined,
                           DenseStorage>;

}  // namespace Sglty

#endif  // SINGULARITYLIB_LIB_HPP