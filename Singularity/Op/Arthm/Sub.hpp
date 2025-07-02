#pragma once

#include <cstddef>

namespace Sglty::Expr {

/**
 * @brief Compile-time matrix subtraction operation.
 *
 * Represents element-wise subtraction of two matrix expressions.
 * Used as the `op_type` in a `Binary<_lhs, _rhs, Sub>` expression node.
 */
struct Sub {
  /**
   * @brief Row count of the result.
   *
   * Matches both operands. Compile-time error if dimensions mismatch.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;

  /**
   * @brief Column count of the result.
   *
   * Matches both operands. Compile-time error if dimensions mismatch.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _lhs::cols;

  /**
   * @brief Resulting core implementation.
   *
   * Assumes both operands share the same `core_impl`.
   */
  template <typename _lhs, typename _rhs>
  using core_impl = typename _lhs::core_impl;

  /**
   * @brief Valid if both operands use the same core implementation.
   */
  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_core_impl =
      std::is_same_v<typename _lhs::core_impl, typename _rhs::core_impl>;

  /**
   * @brief Valid if both operands have identical dimensions.
   */
  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_dimension =
      (_lhs::rows == _rhs::rows) && (_lhs::cols == _rhs::cols);

  /**
   * @brief Computes the element-wise difference `_l(i, j) - _r(i, j)`.
   *
   * @param _l Left-hand side operand.
   * @param _r Right-hand side operand.
   * @param i Row index.
   * @param j Column index.
   * @return Difference of the operands at (i, j).
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
 * @brief Constructs a compile-time subtraction expression.
 *
 * Subtracts two matrix expressions element-wise. Requires both operands to
 * satisfy expression and shape compatibility.
 *
 * @tparam _lhs Left-hand side expression type.
 * @tparam _rhs Right-hand side expression type.
 * @param _l Left operand.
 * @param _r Right operand.
 * @return A `Binary<_lhs, _rhs, Expr::Sub>` expression node.
 */
template <typename _lhs, typename _rhs>
constexpr auto Sub(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

/**
 * @brief Overload of binary `-` for matrix expressions.
 *
 * Allows writing `A - B` for two compatible matrix expressions.
 * Forwards to `Op::Arthm::Sub`.
 *
 * @tparam _lhs Left-hand side expression type.
 * @tparam _rhs Right-hand side expression type.
 * @param _l Left operand.
 * @param _r Right operand.
 * @return A subtraction expression node.
 */
template <typename _lhs, typename _rhs>
constexpr auto operator-(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Types

#include "Impl/Sub.tpp"

// Singularity/Op/Arthm/Sub.hpp
