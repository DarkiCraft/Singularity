#ifndef SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP
#define SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP

#include <type_traits>

using size_t = unsigned long long;

namespace Sglty {

enum class CoreType { Static, Dynamc };
enum class CoreMode { Dense, Sprse };
enum class CoreOrdr { RowMajor, ColMajor, Udefined };

template <CoreType _core_type, CoreMode _core_mode, CoreOrdr _core_ordr>
struct CoreTraits {
  static constexpr CoreType core_type = _core_type;
  static constexpr CoreMode core_mode = _core_mode;
  static constexpr CoreOrdr core_ordr = _core_ordr;
};

template <CoreType _core_type, CoreMode _core_mode, CoreOrdr _core_ordr>
struct is_valid_core_traits
    : std::bool_constant<(_core_mode == CoreMode::Dense &&
                              (_core_ordr == CoreOrdr::RowMajor ||
                               _core_ordr == CoreOrdr::ColMajor) ||
                          _core_mode == CoreMode::Sprse)> {};

template <CoreType _core_type, CoreMode _core_mode, CoreOrdr _core_ordr>
constexpr bool is_valid_core_traits_v =
    is_valid_core_traits<_core_type, _core_mode, _core_ordr>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP

// SingularityLib/Matrix/Traits/Core.hpp