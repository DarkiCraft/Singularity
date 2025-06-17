#ifndef SINGULARITY__HPP
#define SINGULARITY__HPP

#include "Lib/Arithmetic.hpp"
#include "Lib/Core.hpp"
#include "Lib/Expr.hpp"
#include "Lib/Matrix.hpp"
#include "Lib/Traits.hpp"

namespace Sglty {

using std::size_t;

template <typename _Tp,
          size_t _rows,
          size_t _cols,
          Core::Order _core_order = Core::Order::RowMajor>
using DenseMatrix = Matrix<Core::Dense<_Tp, _rows, _cols, _core_order>>;

// template <typename _Tp, size_t _rows, size_t _cols>
// using SparseMatrix = Matrix<SparseCore<_Tp, _rows, _cols>>;

}  // namespace Sglty

#endif  // SINGULARITY__HPP

// Singularity/.hpp