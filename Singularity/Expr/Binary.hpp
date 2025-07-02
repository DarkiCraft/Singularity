#pragma once

#include <cstddef>

#include "Tag.hpp"
#include "../Traits/Expr.hpp"
#include "../Traits/Op.hpp"
#include "../Traits/Core.hpp"

namespace Sglty::Expr {

/**
 * @brief Represents a binary matrix expression.
 *
 * `Binary` is the core structure used to model compile-time expressions of the
 * form `lhs op rhs`, where both operands are themselves valid matrix
 * expressions, and `op` is an operation defining the shape and evaluation
 * logic.
 *
 * This type does not store any matrix data — it only represents the structure
 * of the expression and defers evaluation to the operation logic defined in
 * `op_type`.
 *
 * Used during expression composition and evaluated when passed into a concrete
 * `Matrix`.
 *
 * @tparam _lhs The left-hand side expression type.
 * @tparam _rhs The right-hand side expression type.
 * @tparam _op The operation defining evaluation and result metadata.
 */
template <typename _lhs, typename _rhs, typename _op>
struct Binary : Tag {
  /**
   * @brief The left-hand side expression.
   */
  using lhs_type = _lhs;

  /**
   * @brief The right-hand side expression.
   */
  using rhs_type = _rhs;

  static_assert(Traits::Expr::is_valid_v<lhs_type>,
                "Error: `_lhs` is not a valid expression type.");
  static_assert(Traits::Expr::is_valid_v<rhs_type>,
                "Error: `_rhs` is not a valid expression type.");

  /**
   * @brief The operation tag describing evaluation logic.
   *
   * Must satisfy `Sglty::Traits::Op::is_valid_v`.
   */
  using op_type = _op;

  static_assert(Traits::Op::is_valid_v<op_type>,
                "Error: `_op` is not a valid operation type.");

  /**
   * @brief The resulting core implementation of the expression.
   *
   * This is the type that would back a `Matrix<core_impl>` constructed from
   * this expression.
   */
  using core_impl = typename op_type::core_impl<lhs_type, rhs_type>;

  static_assert(Traits::Core::is_valid_v<core_impl>,
                "Error: `_lhs` and `_rhs` produces invalid `core_impl` type.");

  /**
   * @brief The number of rows in the resulting expression.
   */
  constexpr static std::size_t rows =
      op_type::template rows<lhs_type, rhs_type>;

  /**
   * @brief The number of columns in the resulting expression.
   */
  constexpr static std::size_t cols =
      op_type::template cols<lhs_type, rhs_type>;

  /**
   * @brief Constructs a Binary expression from two operands.
   *
   * The operands must both be valid expression types.
   *
   * @param _l The left-hand expression operand.
   * @param _r The right-hand expression operand.
   */
  constexpr Binary(const lhs_type& _l, const rhs_type& _r);

  /**
   * @brief Evaluates the expression at a given coordinate.
   *
   * Actual evaluation logic is delegated to the `op_type`.
   *
   * @param i The row index.
   * @param j The column index.
   * @return The evaluated value at position (i, j).
   */
  constexpr auto operator()(std::size_t i, std::size_t j) const;

  /// Left-hand operand (stored by value).
  const lhs_type _l;

  /// Right-hand operand (stored by value).
  const rhs_type _r;
};

}  // namespace Sglty::Expr

#include "Impl/Binary.tpp"

// Singularity/Expr/Binary.hpp
