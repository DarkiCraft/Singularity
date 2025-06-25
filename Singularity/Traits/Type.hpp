#pragma once

#include <cstddef>

namespace Sglty::Traits {

template <typename _Tp>
struct Type {
  using size_type       = std::size_t;
  using value_type      = _Tp;
  using difference_type = std::ptrdiff_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = value_type*;
  using const_pointer   = const value_type*;
};

}  // namespace Sglty::Traits

// Singularity/Traits/Type.hpp
