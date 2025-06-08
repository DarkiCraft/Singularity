#ifndef SINGULARITYLIB_MATRIX_TRAITS_SIZE_HPP
#define SINGULARITYLIB_MATRIX_TRAITS_SIZE_HPP

#include <type_traits>

using std::size_t;

namespace Sglty {

/**
 * @brief Trait to represent static matrix dimensions.
 *
 * Holds the following constant expressions:
 * - `rows`
 * - `cols`
 *
 * @tparam _rows Number of rows.
 * @tparam _cols Number of columns.
 */
template <size_t _rows, size_t _cols>
struct SizeTraits {
  static constexpr size_t rows = _rows;
  static constexpr size_t cols = _cols;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TRAITS_SIZE_HPP

// SingularityLib/Matrix/Traits/Size.hpp