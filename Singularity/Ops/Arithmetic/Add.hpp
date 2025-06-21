#pragma once

#include "../../Expr/Base.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs>
struct Add : public Expr::Base<Add<_lhs, _rhs>> {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  const lhs_type _l;
  const rhs_type _r;

  constexpr static size_t rows = lhs_type::rows;  // doesn't matter if it's
  constexpr static size_t cols = rhs_type::cols;  // lhs or rhs, it's equal

  constexpr Add(const lhs_type& _l, const rhs_type& _r) : _l(_l), _r(_r) {
    static_assert(
        lhs_type::rows == rhs_type::rows && _lhs::cols == rhs_type::cols,
        "Error: dimension mismatch between `lhs_type` and `rhs_type`.");
  }

  /**
   * @brief Computes the sum of the elements at the specified row and column from the left and right operands.
   *
   * @param i Row index.
   * @param j Column index.
   * @return The sum of the elements at position (i, j) from both operands.
   */
  constexpr auto operator()(size_t i, size_t j) const {
    return _l(i, j) + _r(i, j);
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arithmetic {

template <typename _lhs, typename _rhs>
/**
 * @brief Creates a matrix addition expression from two operands.
 *
 * Constructs an expression representing the element-wise sum of two matrices or matrix-like objects with matching dimensions.
 *
 * @return An expression object encapsulating the addition of the two operands.
 */
constexpr auto Add(const _lhs& _l, const _rhs& _r) {
  return Expr::Add<_lhs, _rhs>(_l, _r);
}

}  // namespace Sglty::Ops::Arithmetic

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
/**
 * @brief Overloads the + operator to create a matrix addition expression.
 *
 * Enables natural syntax for adding two compatible matrix-like objects, returning an expression representing their element-wise sum.
 *
 * @return Expression representing the sum of the two operands.
 */
constexpr auto operator+(const _lhs& _l, const _rhs& _r) {
  return Ops::Arithmetic::Add(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arithmetic/Add.hpp