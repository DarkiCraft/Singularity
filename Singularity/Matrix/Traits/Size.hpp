#ifndef SINGULARITY_MATRIX_TRAITS_SIZE_HPP
#define SINGULARITY_MATRIX_TRAITS_SIZE_HPP

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
 * @tparam _size_type Type to use for `rows` and `cols`
 */
template <size_t _rows, size_t _cols, typename _size_type>
struct SizeTraits {
  static_assert(std::is_integral_v<_size_type>,
                "Error: Non-integral type passed for _size_type");

  static constexpr _size_type rows = _rows;
  static constexpr _size_type cols = _cols;
};

}  // namespace Sglty

#endif  // SINGULARITY_MATRIX_TRAITS_SIZE_HPP

// Singularity/Matrix/Traits/Size.hpp