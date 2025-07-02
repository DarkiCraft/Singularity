#pragma once

#include <cstddef>
#include <type_traits>

namespace Sglty::Expr {

/**
 * @brief Compile-time scalar multiplication operation.
 *
 * Represents element-wise multiplication of a matrix expression with a scalar.
 * Used as `op_type` in a `Binary<_lhs, _rhs, MulScalar>` expression node.
 */
struct MulScalar {
  /**
   * @brief Row count of the result.
   *
   * Matches the row count of the matrix.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;

  /**
   * @brief Column count of the result.
   *
   * Matches the column count of the matrix.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _lhs::cols;

  /**
   * @brief Resulting core implementation.
   *
   * Same as the matrix operand's core implementation.
   */
  template <typename _lhs, typename _rhs>
  using core_impl = typename _lhs::core_impl;

  /**
   * @brief Evaluates scalar multiplication at the given position.
   *
   * Multiplies the matrix element at `(i, j)` with the scalar operand.
   *
   * @param _l Matrix operand.
   * @param _r Scalar operand.
   * @param i Row index.
   * @param j Column index.
   * @return The product `_l(i, j) * _r`.
   */
  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            std::size_t i,
                            std::size_t j) const;
};

/**
 * @brief Compile-time matrix multiplication operation.
 *
 * Represents matrix-matrix multiplication. Both operands must be valid
 * matrix expressions and have compatible shapes.
 *
 * Used as `op_type` in a `Binary<_lhs, _rhs, MulMatrix>` expression node.
 */
struct MulMatrix {
  /**
   * @brief Row count of the result.
   *
   * Taken from the left-hand side matrix.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;

  /**
   * @brief Column count of the result.
   *
   * Taken from the right-hand side matrix.
   */
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _rhs::cols;

  /**
   * @brief Resulting core implementation.
   *
   * Rebinds the left-hand side core to the new shape.
   */
  template <typename _lhs, typename _rhs>
  using core_impl =
      typename _lhs::core_impl::template core_rebind_size<rows<_lhs, _rhs>,
                                                          cols<_lhs, _rhs>>;

  /**
   * @brief Verifies that both operands use compatible core bases.
   *
   * Required so the result can be bound to a shared underlying core.
   */
  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_core_impl =
      std::is_same_v<typename _lhs::core_impl::core_base,
                     typename _rhs::core_impl::core_base>;

  /**
   * @brief Verifies that matrix multiplication is shape-compatible.
   *
   * Columns of lhs must equal rows of rhs.
   */
  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_dimension = (_lhs::cols == _rhs::rows);

  /**
   * @brief Computes the (i, j) element of the matrix product.
   *
   * Performs the dot product of row `i` of lhs and column `j` of rhs.
   *
   * @param _l Left-hand side matrix.
   * @param _r Right-hand side matrix.
   * @param i Row index.
   * @param j Column index.
   * @return The result of matrix multiplication at position (i, j).
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
 * @brief Multiplies a matrix expression with a scalar (matrix * scalar).
 *
 * Enabled if the left-hand side is a matrix expression and the right-hand side
 * is an arithmetic scalar.
 *
 * @return A Binary expression using `MulScalar`.
 */
template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        Expr::Binary<_lhs, _rhs, Expr::MulScalar>>;

/**
 * @brief Multiplies a scalar with a matrix expression (scalar * matrix).
 *
 * Enabled if the right-hand side is a matrix expression and the left-hand side
 * is an arithmetic scalar.
 *
 * @return A Binary expression using `MulScalar`.
 */
template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        Expr::Binary<_rhs, _lhs, Expr::MulScalar>>;

/**
 * @brief Multiplies two matrix expressions.
 *
 * Enabled only if both operands are valid expressions.
 * Performs standard matrix multiplication using `MulMatrix`.
 *
 * @return A Binary expression using `MulMatrix`.
 */
template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_lhs> &&
                            Traits::Expr::is_valid_v<_rhs>,
                        Expr::Binary<_lhs, _rhs, Expr::MulMatrix>>;

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

/**
 * @brief Operator overload for `*` supporting scalar and matrix multiplication.
 *
 * Supports:
 * - Matrix * Scalar
 * - Scalar * Matrix
 * - Matrix * Matrix
 *
 * Internally dispatches to `Op::Arthm::Mul`.
 */
template <typename _lhs, typename _rhs>
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_lhs> ||
                            Traits::Expr::is_valid_v<_rhs>,
                        decltype(Op::Arthm::Mul(_l, _r))>;

}  // namespace Sglty::Types

#include "Impl/Mul.tpp"

// Singularity/Op/Arthm/Mul.hpp
