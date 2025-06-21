#pragma once

#include <cstddef>
#include <memory>

namespace Sglty::Traits {

template <typename _Tp, typename _Alloc = std::allocator<_Tp>>
struct Type {
  using size_type       = std::size_t;
  using value_type      = _Tp;
  using allocator_type  = _Alloc;
  using difference_type = std::ptrdiff_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = typename std::allocator_traits<_Alloc>::pointer;
  using const_pointer   = typename std::allocator_traits<_Alloc>::const_pointer;
};

}  // namespace Sglty::Traits

// Singularity/Traits/Type.hpp