#pragma once

#include <cstddef>

#include "Core/Enums.hpp"

namespace Sglty::Core {

template <typename, std::size_t, std::size_t, Major>
class Dense;

}  // namespace Sglty::Core

namespace Sglty::Types {

template <typename>
class Matrix;

}  // namespace Sglty::Types

namespace Sglty {

/**
 * @brief Convenience alias for creating a statically sized dense matrix.
 *
 * `DenseMat<T, R, C>` expands to a `Matrix` type backed by a `Dense` core
 * implementation with value type `T` and fixed dimensions `R × C`.
 *
 * Example:
 * ```cpp
 * DenseMat<float, 3, 3> mat;  // 3x3 matrix of floats
 * ```
 *
 * You can optionally override the memory layout (row-major by default):
 * ```cpp
 * DenseMat<double, 4, 2, Core::Major::Col> col_major_mat;
 * ```
 *
 * @tparam _Tp         Value type (e.g., float, int, etc.)
 * @tparam _rows       Number of rows (must be > 0)
 * @tparam _cols       Number of columns (must be > 0)
 * @tparam _core_major Memory layout (row-major or column-major)
 */
template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major = Core::Major::Row>
using DenseMat =
    Sglty::Types::Matrix<Sglty::Core::Dense<_Tp, _rows, _cols, _core_major>>;

}  // namespace Sglty

// Singularity/Convenience.hpp
