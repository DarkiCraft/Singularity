#pragma once

#include "../Core/Enums.hpp"

namespace Sglty::Traits::Core {

/**
 * @brief Maps a combination of core type and major to a concrete trait
 * implementation.
 *
 * Specializations of this struct group metadata for a specific core under one
 * unified type.
 *
 * Example Usage:
 * ```
 * using core_traits = Sglty::Traits::Core::Get<
 *   Sglty::Core::Type::Dense,
 *   Sglty::Core::Major::Row
 * >;
 * //! Constructs a group for a Dense, Row-major core.
 * ```
 *
 * Valid combinations are:
 *
 * - Dense + Row
 *
 * - Dense + Col
 *
 * - Sparse + Undefined
 *
 * @tparam _core_type  Enum for core category
 * @tparam _core_major Enum for major variation
 *
 * This struct is required during matrix construction and is validated
 * accordingly
 *
 * @see Sglty::Core::is_valid_v
 */
template <Sglty::Core::Type _core_type, Sglty::Core::Major _core_major>
struct Get;

}  // namespace Sglty::Traits::Core

namespace Sglty::Traits::Core {

/**
 * @brief Checks whether a core exposes a valid `size_traits` definition.
 *
 * A valid `size_traits` must be a struct of the form:
 * ```
 * struct size_traits {
 *   static constexpr integral_type rows = // some value //;
 *   static constexpr integral_type cols = // some value //;
 * };
 * ```
 * where `integral_type` satisfies `std::is_integral` trait

 * @tparam _core_impl Core implementation type being inspected.
 *
 * A convenience struct is also provided whichalways produces a valid
 * `size_traits` definition. @see `Sglty::Traits::Size::Get`
 *
 * @see Sglty::Core::is_valid_v
 */
template <typename _core_impl>
extern const bool has_size_traits_v;

/**
 * @brief Checks whether a core exposes a valid `type_traits` definition.
 *
 * A valid `type_traits` must be a struct of the form:
 * ```
 * struct type_traits {
 *   using size_type       = // some type //;
 *   using value_type      = // some type //;
 *   using difference_type = // some type //;
 *   using reference       = // some type //;
 *   using const_reference = // some type //;
 *   using pointer         = // some type //;
 *   using const_pointer   = // some type //;
 * };
 * ```
 * Though not explicitly validated, all types must be semantically correct
 *
 * @tparam _core_impl Core implementation type being inspected.
 *
 * A convenience struct is also provided whichalways produces a valid
 * `size_traits` definition. @see `Sglty::Traits::Type::Get`
 *
 * @see Sglty::Core::is_valid_v
 */
template <typename _core_impl>
extern const bool has_type_traits_v;

/**
 * @brief Checks whether a core exposes a valid `core_traits` definition.
 *
 * A valid `core_traits` must be a struct of the form:
 * ```
 * struct core_traits {
 *   static constexpr Sglty::Core::Type core_type   = // some value //;
 *   static constexpr Sglty::Core::Major core_major = // some value //;
 * };
 * ```
 *
 * @tparam _core_impl Core implementation type being inspected.
 *
 * A convenience struct is also provided whichalways produces a valid
 * `size_traits` definition. @see `Sglty::Traits::Core::Get`
 *
 * @see Sglty::Core::is_valid_v
 */
template <typename _core_impl>
extern const bool has_core_traits_v;

/**
 * @brief Checks whether a core exposes a valid `core_rebind_size` + `core_base`
 * pair.
 *
 * A valid rebind trait must satisfy the following:
 *
 * - The core must define a nested `core_base` type
 *
 * - The expression `core_rebind_size<0, 0>` must be valid and return the same
 * type as `core_base`
 *
 * Expected form:
 * ```
 * using core_base = // some core impl //;
 *
 * template <std::size_t NewRows, std::size_t NewCols>
 * using core_rebind_size = // some specialization of core_base //;
 * ```
 *
 * This enables compile-time construction of a new core with different
 * dimensions, while preserving type information and behavioral guarantees.
 *
 * @tparam _core_impl Core implementation type being inspected.
 *
 * @see Sglty::Core::is_valid_v
 */
template <typename _core_impl>
extern const bool has_rebind_size_traits_v;

/**
 * @brief Checks whether a core exposes valid `At()` and `Data()` member
 * functions.
 *
 * Expected signatures:
 * ```
 * reference       At(size_type, size_type);
 * const_reference At(size_type, size_type) const;
 * pointer         Data();
 * const_pointer   Data() const;
 * ```
 * Where all types come from the `type_traits` definition.
 *
 * @tparam _core_impl Core implementation type being inspected.
 *
 * `type_traits` must also be present and valid for this to be meaningful
 *
 * @see Sglty::Core::is_valid_v
 */
template <typename _core_impl>
extern const bool has_member_functions_v;

/**
 * @brief Checks whether a core satisfies all required traits and behaviors.
 *
 * Combines:
 *
 * - `Sglty::Traits::Core::has_size_traits_v`
 *
 * - `Sglty::Traits::Core::has_type_traits_v`
 *
 * - `Sglty::Traits::Core::has_core_traits_v`
 *
 * - `Sglty::Traits::Core::has_rebind_size_traits_v`
 *
 * - `Sglty::Traits::Core::has_member_functions_v`
 *
 * Required for all core implementations used.
 *
 * @tparam _core_impl Core implementation type being validated.
 *
 * @see `Sglty::Traits::Core::has_size_traits_v`
 * @see `Sglty::Traits::Core::has_type_traits_v`
 * @see `Sglty::Traits::Core::has_core_traits_v`
 * @see `Sglty::Traits::Core::has_rebind_size_traits_v`
 * @see `Sglty::Traits::Core::has_member_functions_v`
 */
template <typename _core_impl>
extern const bool is_valid_v;

}  // namespace Sglty::Traits::Core

#include "Impl/Core.tpp"

// Singularity/Traits/Core.hpp
