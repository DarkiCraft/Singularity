#pragma once

namespace Sglty::Traits::Expr {

/**
 * @brief Checks whether an expression type inherits from `Sglty::Expr::Tag`.
 *
 * This is a marker base class used to distinguish expressions types:
 * ```
 * struct SomeExpr : Sglty::Expr::Tag { ... };
 * ```
 * This allows expression templates to be validated or filtered at compile time.
 *
 * @tparam _expr Expression type being inspected.
 *
 * @see Sglty::Expr::is_valid_v
 */
template <typename _expr>
extern const bool has_tag_base_v;

/**
 * @brief Checks whether an expression type exposes a valid expression
 * interface.
 *
 * A valid interface is of the form:
 * ```
 * struct SomeExpr : Sglty::Expr::Tag {
 *   constexpr std::size_t rows = // some value //;
 *   constexpr std::size_t cols = // some value //;
 *
 *   using core_impl = // some type //;
 *
 *   auto operator()(std::size_t, std::size_t) const;
 * };
 * ```
 *
 * @tparam _expr Expression type being inspected.
 *
 * @see Sglty::Traits::Expr::is_valid_v
 */
template <typename _expr>
extern const bool has_interface_v;

/**
 * @brief Checks whether an expression satisfies all required expression
 * semantics.
 *
 * Combines:
 *
 * - `Sglty::Traits::Expr::has_tag_base_v`
 *
 * - `Sglty::Traits::Expr::has_interface_v`
 *
 * Required for all expression types used.
 *
 * @tparam _expr Expression type being validated.
 *
 * Note that `static_asserts` may be present to validate passed Operations
 *
 * @see Sglty::Traits::Expr::has_tag_base_v
 * @see Sglty::Traits::Expr::has_interface_v
 */
template <typename _expr>
extern const bool is_valid_v;

}  // namespace Sglty::Traits::Expr

#include "Impl/Expr.tpp"

// Singularity/Traits/Expr.hpp
