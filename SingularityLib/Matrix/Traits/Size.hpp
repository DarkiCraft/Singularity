#ifndef SINGULARITYLIB_MATRIX_TRAITS_SIZE_HPP
#define SINGULARITYLIB_MATRIX_TRAITS_SIZE_HPP

#include <type_traits>

using std::size_t;

namespace Sglty {

template <size_t _rows, size_t _cols>
struct SizeTraits {
  static constexpr size_t rows = _rows;
  static constexpr size_t cols = _cols;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TRAITS_SIZE_HPP

// SingularityLib/Matrix/Traits/Size.hpp