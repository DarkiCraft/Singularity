#pragma once

namespace Sglty::Traits::Op {

/**
 * @brief Checks whether an operator satisfies unary expression semantics.
 *
 * A valid unary operator is of the form:
 * ```
 * struct SomeOp {
 *   template <typename _expr>
 *   static constexpr std::size_t rows = // some value //;
 *
 *   template <typename _expr>
 *   static constexpr std::size_t cols = // some value //;
 *
 *   template <typename _expr>
 *   using core_impl = // some type //;
 *
 *   template <typename _expr>
 *   static constexpr bool is_valid_core_impl = // some value //;
 *
 *   template <typename _expr>
 *   static constexpr bool is_valid_dimension = // some value //;
 *
 *   auto operator()(const _expr&, std::size_t, std::size_t) const;
 * };
 * ```
 *
 * - `is_valid_core_impl` ensures the derived `core_impl<Expr>` meets trait
 *    requirements. It is generally true for unary operations.
 *
 * - `is_valid_dimension` ensures the operand’s dimensions are valid for this
 *    operation.
 *
 * @tparam _op Operator type being inspected.
 *
 * @see Sglty::Traits::Op::is_valid_v
 */
template <typename _op>
extern const bool is_unary_v;

/**
 * @brief Checks whether an operator satisfies binary expression semantics.
 *
 * A valid binary operator is of the form:
 * ```
 * struct SomeOp {
 *   template <typename _lhs, typename _rhs>
 *   static constexpr std::size_t rows = // some value //;
 *
 *   template <typename _lhs, typename _rhs>
 *   static constexpr std::size_t cols = // some value //;
 *
 *   template <typename _lhs, typename _rhs>
 *   using core_impl = // some type //;
 *
 *   template <typename _lhs, typename _rhs>
 *   static constexpr bool is_valid_core_impl = // some value //;
 *
 *   template <typename _lhs, typename _rhs>
 *   static constexpr bool is_valid_dimension = // some value //;
 *
 *   auto operator()(const _lhs&, const _rhs&, std::size_t, std::size_t) const;
 * };
 * ```
 * - `is_valid_core_impl` ensures the derived `core_impl<Expr>` meets trait
 *    requirements. It generally validates if `_lhs` and `_rhs` produce the
 *    same core_impl.
 *
 * - `is_valid_dimension` ensures the operand’s dimensions are valid for this
 *    operation.
 *
 * @tparam _op Operator type being inspected.
 *
 * @see Sglty::Traits::Op::is_valid_v
 */
template <typename _op>
extern const bool is_binary_v;

/**
 * @brief Checks whether an operator satisfies either unary or binary semantics.
 *
 * Combines:
 *
 * - `is_unary_op_v`
 *
 * - `is_binary_op_v`
 *
 * This is the primary check used for validating operator objects in expression
 * templates.
 *
 * @tparam _op Operator type being validated.
 *
 * @see Sglty::Traits::Expr::is_unary_op_v
 * @see Sglty::Traits::Expr::is_binary_op_v
 */
template <typename _op>
extern const bool is_valid_v;

}  // namespace Sglty::Traits::Op

#include "Impl/Op.tpp"

// Singularity/Traits/Op/hpp