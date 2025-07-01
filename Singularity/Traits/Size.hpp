#pragma once

#include <cstddef>
#include <type_traits>

namespace Sglty::Traits::Size {

/**
 * @brief Maps dimension values and size type to a compile-time `size_traits`
 * definition.
 *
 * This struct is used to define static dimensions and size type in a reusable
 * format.
 *
 * Example Usage:
 * ```
 * using size_traits = Sglty::Traits::Size::Get<3, 4, std::size_t>;
 * //! The generated struct will contain:
 * static constexpr std::size_t rows = 3;
 * static constexpr std::size_t cols = 4;
 * ```
 * `_size_type` must be an integral type.
 *
 * @tparam _rows       Row count
 * @tparam _cols       Column count
 * @tparam _size_type  Integral type used for dimensions
 *
 * This struct is required during matrix construction and is validated
 * accordingly
 *
 * @see Sglty::Traits::Core::has_size_traits_v
 */
template <std::size_t _rows, std::size_t _cols, typename _size_type>
struct Get {
  static_assert(std::is_integral_v<_size_type>,
                "Error: Non-integral type passed for `_size_type`");

  static constexpr _size_type rows = _rows;
  static constexpr _size_type cols = _cols;
};

}  // namespace Sglty::Traits::Size

// Singularity/Traits/Size.hpp
