#pragma once

#include <cstddef>

#include "../../Expr/Unary.hpp"

namespace Sglty::Expr {

/**
 * @brief Compile-time unary negation operation.
 *
 * Represents `-matrix` or `-expression`. Produces a new matrix expression
 * where each element is the negation of the original.
 *
 * Used as `op_type` in `Unary<_operand, Neg>` expression nodes.
 */
struct Neg {
  /**
   * @brief Row count of the result.
   *
   * Matches the input operand.
   */
  template <typename _operand>
  constexpr static std::size_t rows = _operand::rows;

  /**
   * @brief Column count of the result.
   *
   * Matches the input operand.
   */
  template <typename _operand>
  constexpr static std::size_t cols = _operand::cols;

  /**
   * @brief Resulting core implementation.
   *
   * Propagates the operand’s `core_impl` type.
   */
  template <typename _operand>
  using core_impl = typename _operand::core_impl;

  /**
   * @brief Always valid—negation preserves core layout.
   */
  template <typename>
  constexpr static bool is_valid_core_impl = true;

  /**
   * @brief Always valid—negation does not change dimensions.
   */
  template <typename>
  constexpr static bool is_valid_dimension = true;

  /**
   * @brief Computes the element-wise negation of the operand.
   *
   * @param op Operand expression.
   * @param i Row index.
   * @param j Column index.
   * @return `-op(i, j)`
   */
  template <typename _operand>
  constexpr auto operator()(const _operand& op,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Op::Arthm {

/**
 * @brief Wraps an expression in a compile-time negation node.
 *
 * Enables negation like `-matrix` by producing a `Unary<_operand, Expr::Neg>`.
 *
 * @tparam _operand A valid matrix expression.
 * @param _o Operand to negate.
 * @return A unary negation expression.
 */
template <typename _operand>
constexpr auto Neg(const _operand& _o);

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

/**
 * @brief Overload of unary `-` for matrix expressions.
 *
 * Forwards to `Op::Arthm::Neg`. Produces a compile-time negation node.
 *
 * @tparam _operand A valid matrix expression.
 * @param _o Operand to negate.
 * @return A unary expression wrapping the negation.
 */
template <typename _operand>
constexpr auto operator-(const _operand& _o);

}  // namespace Sglty::Types

#include "Impl/Neg.tpp"

// Singularity/Op/Arthm/Neg.hpp
