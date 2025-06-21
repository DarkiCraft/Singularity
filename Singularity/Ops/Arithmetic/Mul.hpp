#pragma once

#include <type_traits>

#include "../../Expr/Base.hpp"
#include "../../Traits/Expr.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs>
struct MulScalar : public Expr::Base<MulScalar<_lhs, _rhs>> {
  using lhs_type = _lhs;  // expression
  using rhs_type = _rhs;  // scalar

  const lhs_type _l;
  const rhs_type _r;

  constexpr static size_t rows = lhs_type::rows;  // doesn't matter if it's
  constexpr static size_t cols = lhs_type::cols;  /**
       * @brief Constructs a scalar multiplication expression with the given expression and scalar.
       *
       * @param _l The left-hand side expression to be multiplied.
       * @param _r The scalar value to multiply the expression by.
       */

  constexpr MulScalar(const lhs_type& _l, const rhs_type& _r)
      : _l(_l), _r(_r) {}

  /**
   * @brief Returns the element at position (i, j) of the expression multiplied by the scalar.
   *
   * @param i Row index.
   * @param j Column index.
   * @return The product of the (i, j) element of the left-hand side expression and the scalar.
   */
  constexpr auto operator()(size_t i, size_t j) const {
    return _l(i, j) * _r;
  }
};

template <typename _lhs, typename _rhs>
struct MulMatrix : public Expr::Base<MulMatrix<_lhs, _rhs>> {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  const lhs_type& _l;
  const rhs_type& _r;

  static_assert(_lhs::cols == _rhs::rows,
                "Error: dimension mismatch between `_lhs` and `_rhs`");

  constexpr static size_t rows = lhs_type::rows;
  constexpr static size_t cols = rhs_type::cols;

  /**
       * @brief Constructs a matrix multiplication expression from two compatible matrix expressions.
       *
       * @param _l Left-hand side matrix expression.
       * @param _r Right-hand side matrix expression.
       */
      constexpr MulMatrix(const lhs_type& _l, const rhs_type& _r)
      : _l(_l), _r(_r) {}

  /**
   * @brief Computes the (i, j) element of the matrix product.
   *
   * Calculates the dot product of the i-th row of the left-hand side expression and the j-th column of the right-hand side expression.
   *
   * @param i Row index.
   * @param j Column index.
   * @return The value at position (i, j) in the resulting matrix.
   */
  constexpr auto operator()(size_t i, size_t j) const {
    decltype(_l(0, 0) * _r(0, 0)) sum{};  // default initialize the result type
    size_t inner_dim = lhs_type::cols;    // = rhs_type::rows
    for (size_t k = 0; k < inner_dim; k++) {
      sum += _l(i, k) * _r(k, j);
    }
    return sum;
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arithmetic {

template <typename _lhs, typename _rhs>
/**
 * @brief Creates an expression representing the multiplication of an expression by a scalar.
 *
 * @return An expression template for element-wise multiplication of the left-hand side expression and the right-hand side scalar.
 */
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        Expr::MulScalar<_lhs, _rhs>> {
  return Expr::MulScalar<_lhs, _rhs>(_l, _r);
}

template <typename _lhs, typename _rhs>
/**
 * @brief Creates an expression representing the product of a scalar and an expression, with the scalar on the left.
 *
 * Returns an expression template for multiplying a scalar value by an expression, enabling scalar multiplication in the form `scalar * expression`.
 *
 * @return Expression representing the scalar-expression product.
 */
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        Expr::MulScalar<_rhs, _lhs>> {
  return Expr::MulScalar<_rhs, _lhs>(_r, _l);
}

template <typename _lhs, typename _rhs>
/**
 * @brief Constructs a matrix multiplication expression from two matrix expressions.
 *
 * Returns an expression representing the product of two matrix expressions, with dimensions checked at compile time.
 *
 * @return Expression template representing the matrix-matrix product.
 */
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            Sglty::is_expression_v<_rhs>,
                        Expr::MulMatrix<_lhs, _rhs>> {
  return Expr::MulMatrix<_lhs, _rhs>(_l, _r);
}

}  // namespace Sglty::Ops::Arithmetic

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
/**
 * @brief Overloads the multiplication operator for expressions and scalars.
 *
 * Enables multiplication between matrix expressions and/or scalars, returning an expression template representing the result. Supports scalar-matrix, matrix-scalar, and matrix-matrix multiplication with compile-time dimension checks.
 *
 * @return An expression template representing the product of the operands.
 */
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> ||
                            Sglty::is_expression_v<_rhs>,
                        decltype(Ops::Arithmetic::Mul(_l, _r))> {
  return Ops::Arithmetic::Mul(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arithmetic/Mul.hpp