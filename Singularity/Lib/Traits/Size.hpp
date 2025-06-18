#ifndef SINGULARITY_TRAITS_SIZE_HPP
#define SINGULARITY_TRAITS_SIZE_HPP

#include <type_traits>

namespace Sglty {

using std::size_t;

namespace Traits {

template <size_t _rows, size_t _cols, typename _size_type>
struct Size {
  static_assert(std::is_integral_v<_size_type>,
                "Error: Non-integral type passed for _size_type");

  static constexpr _size_type rows = _rows;
  static constexpr _size_type cols = _cols;
};

}  // namespace Traits

}  // namespace Sglty

#endif  // SINGULARITY_TRAITS_SIZE_HPP

// Singularity/Traits/Size.hpp