#pragma once

#include <cstddef>
#include <type_traits>

namespace Sglty::Traits {

template <std::size_t _rows, std::size_t _cols, typename _size_type>
struct Size {
  static_assert(std::is_integral_v<_size_type>,
                "Error: Non-integral type passed for _size_type");

  static constexpr _size_type rows = _rows;
  static constexpr _size_type cols = _cols;
};

}  // namespace Sglty::Traits

// Singularity/Traits/Size.hpp
