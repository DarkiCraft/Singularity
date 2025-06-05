#ifndef SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP
#define SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP

#include <type_traits>

using std::size_t;

namespace Sglty {

enum class CoreMode { Dense, Sprse };
enum class CoreOrdr { RowMajor, ColMajor, Udefined };

template <CoreMode _core_mode, CoreOrdr _core_ordr>
struct CoreTraits {
  static constexpr CoreMode core_mode = _core_mode;
  static constexpr CoreOrdr core_ordr = _core_ordr;
};

template <typename core_traits>
struct is_valid_core_traits
    : std::bool_constant<(core_traits::core_mode == CoreMode::Dense &&
                              (core_traits::core_ordr == CoreOrdr::RowMajor ||
                               core_traits::core_ordr == CoreOrdr::ColMajor) ||
                          core_traits::core_mode == CoreMode::Sprse)> {};

template <typename core_traits>
constexpr bool is_valid_core_traits_v =
    is_valid_core_traits<core_traits>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP

// SingularityLib/Matrix/Traits/Core.hpp