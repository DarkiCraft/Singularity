#pragma once

#include <cstddef>

namespace Sglty::Expr {

/**
 * @brief Compile-time matrix addition operation.
 *
 * Defines how to add two matrix expressions at compile time. Used as the
 * `op_type` in a `Binary<_lhs, _rhs, Add>` expression node.
 *
 * Both operands must:
 * - Be the same shape (`rows` and `cols` match)
 * - Have the same `core_impl` type
 */
struct Add {
  /**
   * @brief Row count of the result.
   *
   * Matches the row count of both operands.
   *
   * @tparam _lhs Left-hand side expression.
   * @tparam _rhs Right-hand side expression.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;

  /**
   * @brief Column count of the result.
   *
   * Matches the column count of both operands.
   *
   * @tparam _lhs Left-hand side expression.
   * @tparam _rhs Right-hand side expression.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _lhs::cols;

  /**
   * @brief The core implementation used by the resulting expression.
   *
   * Only valid if both operands share the same core implementation.
   *
   * @tparam _lhs Left-hand side expression.
   * @tparam _rhs Right-hand side expression.
   */
  template <typename _lhs, typename _rhs>
  using core_impl = typename _lhs::core_impl;

  /**
   * @brief Verifies that both operands use the same core implementation.
   */
  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_core_impl =
      std::is_same_v<typename _lhs::core_impl, typename _rhs::core_impl>;

  /**
   * @brief Verifies that both operands have the same shape.
   */
  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_dimension =
      (_lhs::rows == _rhs::rows) && (_lhs::cols == _rhs::cols);

  /**
   * @brief Evaluates the sum of two matrix expressions at a given position.
   *
   * The actual addition is done element-wise: `l(i, j) + r(i, j)`.
   *
   * @param _l Left operand.
   * @param _r Right operand.
   * @param i Row index.
   * @param j Column index.
   * @return The element-wise sum at (i, j).
   */
  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Op::Arthm {

/**
 * @brief Constructs a binary expression for matrix addition.
 *
 * Wraps `_l` and `_r` in a `Binary` expression node using the `Expr::Add`
 * operation.
 *
 * @tparam _lhs Left-hand side expression.
 * @tparam _rhs Right-hand side expression.
 * @param _l The left operand.
 * @param _r The right operand.
 * @return A compile-time binary addition expression.
 */
template <typename _lhs, typename _rhs>
constexpr auto Add(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

/**
 * @brief Operator overload for matrix addition.
 *
 * Enables using `+` between any two valid matrix expressions.
 * Internally forwards to `Op::Arthm::Add`.
 *
 * @tparam _lhs Left-hand side expression.
 * @tparam _rhs Right-hand side expression.
 * @param _l The left operand.
 * @param _r The right operand.
 * @return A binary addition expression.
 */
template <typename _lhs, typename _rhs>
constexpr auto operator+(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Types

#include "Impl/Add.tpp"

// Singularity/Op/Arthm/Add.hpp
