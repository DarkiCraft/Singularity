#ifndef SINGULARITYLIB_LIB_HPP
#define SINGULARITYLIB_LIB_HPP

#include "Matrix.hpp"
#include "Matrix/Core/Dense.hpp"
#include "Matrix/Core/Sprse.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp,
          size_t _rows,
          size_t _cols,
          CoreOrdr _core_ordr = CoreOrdr::RowMajor>
using DenseMatrix = Matrix<DenseCore<_Tp, _rows, _cols, _core_ordr>>;

template <typename _Tp, size_t _rows, size_t _cols>
using SprseMatrix = Matrix<SprseCore<_Tp, _rows, _cols>>;

}  // namespace Sglty

#endif  // SINGULARITYLIB_LIB_HPP

// SingularityLib/Lib.hpp