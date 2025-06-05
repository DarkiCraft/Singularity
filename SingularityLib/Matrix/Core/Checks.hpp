#ifndef SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP
#define SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP

#include <type_traits>

#include "../Traits/Core.hpp"
#include "../Traits/Type.hpp"

using std::size_t;

namespace Sglty {

/*===========================================================================*/

/**
 * @brief Trait to detect presence of required type aliases in a core
 * implementation.
 *
 * Checks for the definition of the following nested types:
 * - value_type
 * - allocator_type
 * - reference
 * - const_reference
 * - pointer
 * - const_pointer
 * - core_traits
 *
 * If all these nested types exist, `has_type_traits<_core_impl>` inherits from
 * `std::true_type`, otherwise from `std::false_type`.
 *
 * @tparam _core_impl The type to check for the required nested type aliases.
 * @tparam _enable SFINAE helper parameter (default is void).
 */
template <typename, typename _enable = void>
struct has_type_traits : std::false_type {};

/**
 * @brief Specialization for types that have all required nested type aliases.
 */
template <typename _core_impl>
struct has_type_traits<_core_impl,
                       std::void_t<typename _core_impl::value_type,
                                   typename _core_impl::allocator_type,
                                   typename _core_impl::reference,
                                   typename _core_impl::const_reference,
                                   typename _core_impl::pointer,
                                   typename _core_impl::const_pointer,
                                   typename _core_impl::core_traits>>
    : std::true_type {};

/**
 * @brief Convenience variable template to check if a type has the required
 * nested type aliases.
 *
 * Evaluates to true if `_core_impl` has all the required nested type aliases,
 * false otherwise.
 *
 * @tparam _core_impl The type to check.
 */
template <typename _core_impl>
constexpr bool has_type_traits_v = has_type_traits<_core_impl>::value;

/*===========================================================================*/

/**
 * @brief Trait to check if a type has a valid nested `core_traits` member.
 *
 * Checks if the type `_core_impl` defines a nested type `core_traits` with two
 * constexpr enum values:
 * - `core_mode` of type `CoreMode`
 * - `core_ordr` of type `CoreOrdr`
 *
 * If all conditions are met, `has_core_traits<_core_impl>` inherits from
 * `std::true_type`, otherwise from `std::false_type`.
 *
 * @tparam _core_impl The type to check for nested `core_traits`.
 * @tparam _enable SFINAE helper parameter (default is void).
 */
template <typename, typename _enable = void>
struct has_core_traits : std::false_type {};

/**
 * @brief Specialization that detects presence and correct types of nested
 * `core_traits`.
 */
template <typename _core_impl>
struct has_core_traits<
    _core_impl,
    std::void_t<typename _core_impl::core_traits,
                std::enable_if_t<
                    std::is_same_v<decltype(_core_impl::core_traits::core_mode),
                                   const CoreMode>>,
                std::enable_if_t<
                    std::is_same_v<decltype(_core_impl::core_traits::core_ordr),
                                   const CoreOrdr>>>> : std::true_type {};

/**
 * @brief Convenience variable template to check if a type has a valid nested
 * `core_traits` member.
 *
 * Evaluates to true if `_core_impl` has a nested `core_traits` type with the
 * correct enum members and types; false otherwise.
 *
 * @tparam _core_impl The type to check.
 */
template <typename _core_impl>
constexpr bool has_core_traits_v = has_core_traits<_core_impl>::value;

/*===========================================================================*/

/**
 * @brief Trait to check if a type has required static member functions Rows()
 * and Cols(), both returning integral types.
 *
 * Checks for the existence of static functions:
 * - Rows()
 * - Cols()
 *
 * If both exist and return integral types, `has_static_functions<_core_impl>`
 * inherits from `std::true_type`, otherwise from `std::false_type`.
 *
 * @tparam _core_impl The type to check.
 * @tparam _enable SFINAE helper parameter (default is void).
 */
template <typename _core_impl, typename _enable = void>
struct has_static_functions : std::false_type {};

/**
 * @brief Specialization that validates presence and return types of Rows()
 * and Cols().
 */
template <typename _core_impl>
struct has_static_functions<
    _core_impl,
    std::void_t<decltype(_core_impl::Rows()), decltype(_core_impl::Cols())>> {
  static constexpr bool value =
      std::is_integral_v<decltype(_core_impl::Rows())> &&
      std::is_integral_v<decltype(_core_impl::Cols())>;
};

/**
 * @brief Convenience variable template to check if a type has valid static
 * member functions Rows() and Cols() with integral return types.
 *
 * Evaluates to true if `_core_impl` has valid static member functions Rows()
 * and Cols(), both returning integral types; false otherwise.
 *
 * @tparam _core_impl The type to check.
 */
template <typename _core_impl>
constexpr bool has_static_functions_v = has_static_functions<_core_impl>::value;

/*===========================================================================*/

/**
 * @brief Trait to check if a type has required member functions At() and Data()
 * with proper const and non-const overloads and expected return types.
 *
 * Checks for the existence of member functions:
 * - At(size_t, size_t) returning `reference`
 * - At(size_t, size_t) const returning `const_reference`
 * - Data() returning `pointer`
 * - Data() const returning `const_pointer`
 *
 * The type `_core_impl` must define these member type aliases:
 * - value_type
 * - reference
 * - const_reference
 * - pointer
 * - const_pointer
 *
 * If all conditions are met, `has_member_functions<_core_impl>` inherits from
 * `std::true_type`, otherwise from `std::false_type`.
 *
 * @tparam _core_impl The type to check.
 * @tparam _enable SFINAE helper parameter (default is void).
 */
template <typename _core_impl, typename _enable = void>
struct has_member_functions : std::false_type {};

/**
 * @brief Specialization that validates presence, overloads, and return types
 * of At() and Data() member functions.
 *
 * Validates that:
 * - `_core_impl::At(size_t, size_t)` returns `reference`
 * - `const _core_impl::At(size_t, size_t)` returns `const_reference`
 * - `_core_impl::Data()` returns `pointer`
 * - `const _core_impl::Data()` returns `const_pointer`
 *
 * Ensures const-correctness and consistency with the type's member typedefs.
 */
template <typename _core_impl>
struct has_member_functions<
    _core_impl,
    std::void_t<decltype(std::declval<_core_impl&>().At(size_t{}, size_t{})),
                decltype(std::declval<const _core_impl&>().At(size_t{},
                                                              size_t{})),
                decltype(std::declval<_core_impl&>().Data()),
                decltype(std::declval<const _core_impl&>().Data())>> {
 private:
  using value_type      = typename _core_impl::value_type;
  using reference       = typename _core_impl::reference;
  using const_reference = typename _core_impl::const_reference;
  using pointer         = typename _core_impl::pointer;
  using const_pointer   = typename _core_impl::const_pointer;

  static constexpr bool _m_At_nonconst_returns_ref =
      std::is_same_v<decltype(std::declval<_core_impl&>().At(size_t{},
                                                             size_t{})),
                     reference>;

  static constexpr bool _m_At_const_returns_cref =
      std::is_same_v<decltype(std::declval<const _core_impl&>().At(size_t{},
                                                                   size_t{})),
                     const_reference>;

  static constexpr bool _m_Data_nonconst_returns_ptr =
      std::is_same_v<decltype(std::declval<_core_impl&>().Data()), pointer>;

  static constexpr bool _m_Data_const_returns_cptr =
      std::is_same_v<decltype(std::declval<const _core_impl&>().Data()),
                     const_pointer>;

 public:
  static constexpr bool value =
      _m_At_nonconst_returns_ref   && _m_At_const_returns_cref   &&
      _m_Data_nonconst_returns_ptr && _m_Data_const_returns_cptr;
};

/**
 * @brief Convenience variable template to check if a type has valid member
 * functions At() and Data() with expected overloads and return types.
 *
 * Evaluates to true if `_core_impl` has valid member functions At() and Data()
 * as specified; false otherwise.
 *
 * @tparam _core_impl The type to check.
 */
template <typename _core_impl>
constexpr bool has_member_functions_v = has_member_functions<_core_impl>::value;

/*===========================================================================*/

// template <typename _core_impl>
// struct is_valid_core_implementation
//     : std::conjunction<has_type_traits<_core_impl>,
//                        has_core_traits<_core_impl>,
//                        has_static_methods<_core_impl>,
//                        has_member_functions<_core_impl>> {};

// template <typename _core_impl>
// constexpr bool is_valid_core_implementation_v =
//     is_valid_core_implementation<_core_impl>::value;

/*===========================================================================*/

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP

// SingularityLib/Matrix/Core/Checks.hpp