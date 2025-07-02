#pragma once

#include <cstddef>

#include "../Traits/Core.hpp"
#include "../Traits/Expr.hpp"
#include "../Traits/Op.hpp"
#include "Tag.hpp"

namespace Sglty::Expr {

/**
 * @brief Represents a unary matrix expression.
 *
 * `Unary` models compile-time matrix expressions of the form `op operand`,
 * where the operand is itself a valid matrix expression, and the operation
 * defines the transformation logic.
 *
 * This is a lightweight wrapper that encodes the structure of the expression
 * and defers all evaluation logic to the `op_type`.
 *
 * Used in expression trees and evaluated when passed into a `Matrix`.
 *
 * @tparam _operand The operand expression type.
 * @tparam _op The operation defining evaluation and result traits.
 */
template <typename _operand, typename _op>
struct Unary : Tag {
  /**
   * @brief The expression being transformed.
   */
  using operand_type = _operand;

  static_assert(Traits::Expr::is_valid_v<operand_type>,
                "Error: `_operand` is not a valid expression type.");

  /**
   * @brief The operation defining how to evaluate the operand.
   *
   * Must satisfy `Sglty::Traits::Op::is_valid_v`.
   */
  using op_type = _op;

  static_assert(Traits::Op::is_valid_v<op_type>,
                "Error: `_op` is not a valid operation type.");

  /**
   * @brief The resulting core implementation of the expression.
   *
   * Used to construct a concrete matrix when this expression is evaluated.
   */
  using core_impl = typename op_type::core_impl<operand_type>;

  static_assert(Traits::Core::is_valid_v<core_impl>,
                "Error: `_operand` produces invalid core_impl type.");

  /**
   * @brief Number of rows in the resulting expression.
   */
  constexpr static std::size_t rows = op_type::template rows<operand_type>;

  /**
   * @brief Number of columns in the resulting expression.
   */
  constexpr static std::size_t cols = op_type::template cols<operand_type>;

  /**
   * @brief Constructs a unary expression node.
   *
   * Stores the operand and defers evaluation to the `op_type`.
   *
   * @param _o The operand expression to wrap.
   */
  constexpr Unary(const operand_type& _o);

  /**
   * @brief Evaluates the expression at a given coordinate.
   *
   * Actual logic is implemented by the `op_type`.
   *
   * @param i The row index.
   * @param j The column index.
   * @return The evaluated result at position (i, j).
   */
  constexpr auto operator()(std::size_t i, std::size_t j) const;

  /// Stored operand (by value).
  const operand_type _o;
};

}  // namespace Sglty::Expr

#include "Impl/Unary.tpp"

// Singularity/Expr/Unary.hpp
