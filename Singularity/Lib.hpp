#ifndef SINGULARITY__HPP
#define SINGULARITY__HPP

#include "Matrix.hpp"
#include "Matrix/Core/Dense.hpp"
#include "Matrix/Core/Sprse.hpp"

using std::size_t;

namespace Sglty {

template <typename _Tp,
          size_t _rows,
          size_t _cols,
          CoreOrdr _core_ordr = CoreOrdr::RowMajor>
using DenseMatrix = Matrix<DenseCore<_Tp, _rows, _cols, _core_ordr>>;

template <typename _Tp, size_t _rows, size_t _cols>
using SprseMatrix = Matrix<SprseCore<_Tp, _rows, _cols>>;

}  // namespace Sglty

#endif  // SINGULARITY__HPP

// Singularity/.hpp