#ifndef SINGULARITYLIB_LIB_HPP
#define SINGULARITYLIB_LIB_HPP

#include "Matrix.hpp"
#include "Matrix/DenseStorage.hpp"
#include "Matrix/SprseStorage.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp,
          size_t _rows,
          size_t _cols,
          StorageOrdr _st_ordr = StorageOrdr::RowMajor>
using DenseMatrix = Matrix<DenseStorage<_Tp, _rows, _cols, _st_ordr>>;

template <typename _Tp, size_t _rows, size_t _cols>
using SprseMatrix = Matrix<SprseStorage<_Tp, _rows, _cols>>;

}  // namespace Sglty

#endif  // SINGULARITYLIB_LIB_HPP

// SingularityLib/Lib.hpp