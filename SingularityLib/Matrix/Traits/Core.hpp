#ifndef SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP
#define SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP

#include <type_traits>

using std::size_t;

namespace Sglty {

/**
 * @brief Core implementation density modes.
 *
 * Represents the mode of data storage:
 * - `Dense`
 * - `Sprse`
 */
enum class CoreMode { Dense, Sprse };

/**
 * @brief Core implementation memory orderings.
 *
 * Represents the ordering of stored data:
 * - `RowMajor`
 * - `ColMajor`
 * - `Udefined`
 */
enum class CoreOrdr { RowMajor, ColMajor, Udefined };

/**
 * @brief Trait class to bind compile-time `CoreMode` and `CoreOrdr`.
 *
 * Holds the following constant expressions:
 * - `core_mode`
 * - `core_ordr`
 *
 * Used to define core implementation metadata.
 *
 * @tparam _core_mode The core mode to use.
 * @tparam _core_ordr The core ordering to use.
 */
template <CoreMode _core_mode, CoreOrdr _core_ordr>
struct CoreTraits {
  static constexpr CoreMode core_mode = _core_mode;
  static constexpr CoreOrdr core_ordr = _core_ordr;
};

/**
 * @brief Trait to check if a type provides valid core trait constants.
 *
 * Checks for the presence of:
 * - `core_mode`
 * - `core_ordr`
 *
 * Evaluates to `true` if:
 * - `core_mode` is `CoreMode::Dense` *and* `core_ordr` is `RowMajor` or
 * `ColMajor`
 * - or if `core_mode` is `CoreMode::Sprse`
 * Otherwise, evaluates to `false`.
 *
 * @tparam _core_traits The type to check.
 * @tparam _enable SFINAE helper parameter (default is void).
 */
template <typename, typename = void>
struct is_valid_core_traits : std::false_type {};

/**
 * @brief Specialization that detects presence and validates values of
 * `core_mode` and `core_ordr`.
 */
template <typename _core_traits>
struct is_valid_core_traits<_core_traits,
                            std::void_t<decltype(_core_traits::core_mode),
                                        decltype(_core_traits::core_ordr)>>
    : std::bool_constant<(_core_traits::core_mode == CoreMode::Dense &&
                          (_core_traits::core_ordr == CoreOrdr::RowMajor ||
                           _core_traits::core_ordr == CoreOrdr::ColMajor)) ||
                         _core_traits::core_mode == CoreMode::Sprse> {};

/**
 * @brief Convenience variable template to check if a type has valid `core_mode`
 * and `core_ordr`.
 *
 * Evaluates to true if `_core_traits` has valid `core_mode` and `core_ordr`;
 * false otherwise.
 *
 * @tparam core_traits The type to check.
 */
template <typename core_traits>
constexpr bool is_valid_core_traits_v =
    is_valid_core_traits<core_traits>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_TRAITS_CORE_HPP

// SingularityLib/Matrix/Traits/Core.hpp