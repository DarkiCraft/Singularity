#ifndef SINGULARITYLIB_MATRIX_TYPE_TRAITS_HPP
#define SINGULARITYLIB_MATRIX_TYPE_TRAITS_HPP

#include <memory>

namespace Sglty {

template <typename _Tp, typename Alloc = std::allocator<_Tp>>
struct TypeTraits {
  using value_type      = _Tp;
  using allocator_type  = Alloc;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = typename std::allocator_traits<Alloc>::pointer;
  using const_pointer   = typename std::allocator_traits<Alloc>::const_pointer;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TYPE_TRAITS_HPP

// SingularityLib/Matrix/TypeTraits.hpp