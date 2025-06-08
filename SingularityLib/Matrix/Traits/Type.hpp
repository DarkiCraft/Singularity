#ifndef SINGULARITYLIB_MATRIX_TRAITS_TYPE_HPP
#define SINGULARITYLIB_MATRIX_TRAITS_TYPE_HPP

#include <cstddef>
#include <memory>

using std::ptrdiff_t;
using std::size_t;

namespace Sglty {

/**
 * @brief Trait to define element and allocator types with related aliases.
 *
 * Defines the following type members:
 * - `value_type`
 * - `size_type`
 * - `allocator_type`
 * - `difference_type`
 * - `reference`
 * - `const_reference`
 * - `pointer`
 * - `const_pointer`
 *
 * @tparam _Tp The element type.
 * @tparam _Alloc The allocator type (default is `std::allocator<_Tp>`).
 */
template <typename _Tp,
          typename _size_type       = size_t,
          typename _Alloc           = std::allocator<_Tp>,
          typename _difference_type = ptrdiff_t>
struct TypeTraits {
  using value_type      = _Tp;
  using size_type       = _size_type;
  using allocator_type  = _Alloc;
  using difference_type = _difference_type;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = typename std::allocator_traits<_Alloc>::pointer;
  using const_pointer   = typename std::allocator_traits<_Alloc>::const_pointer;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TRAITS_TYPE_HPP

// SingularityLib/Matrix/Traits/Type.hpp