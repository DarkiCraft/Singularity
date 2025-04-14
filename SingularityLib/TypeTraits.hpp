#ifndef SINGULARITYLIB_TYPE_TRAITS_HPP
#define SINGULARITYLIB_TYPE_TRAITS_HPP

namespace Sglty {

template <typename _Tp>
struct TypeTraits {
  using value_type      = _Tp;
  using reference       = value_type&;
  using const_reference = const _Tp&;
  using pointer         = _Tp*;
  using const_pointer   = const _Tp*;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_TYPE_TRAITS_HPP

// SingularityLib/TypeTraits.hpp