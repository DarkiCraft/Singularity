#pragma once

#include <cstddef>

namespace Sglty::Traits::Type {

/**
 * @brief Maps a value type to a standard `type_traits` definition.
 *
 * This struct defines all common typedefs needed for matrix value access and
 * iteration.
 *
 * Example Usage:
 * ```
 * using type_traits = Sglty::Traits::Type::Get<float>;
 * //! The generated struct will contain:
 * using value_type      = float;
 * using size_type       = std::size_t;
 * using difference_type = std::ptrdiff_t;
 * using reference       = float&;
 * using const_reference = const float&;
 * using pointer         = float*;
 * using const_pointer   = const float*;
 * ```
 *
 * @tparam _Tp Value type
 *
 * This struct is required during matrix construction and is validated
 * accordingly.
 *
 * The user may define their own typedefs if they are semantically correct
 *
 * @see Sglty::Traits::Core::has_type_traits_v
 */
template <typename _Tp>
struct Get {
  using size_type       = std::size_t;
  using value_type      = _Tp;
  using difference_type = std::ptrdiff_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = value_type*;
  using const_pointer   = const value_type*;
};

}  // namespace Sglty::Traits::Type

// Singularity/Traits/Type.hpp
