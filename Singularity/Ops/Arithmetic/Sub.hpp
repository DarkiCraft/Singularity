#pragma once

#include "../../Expr/Base.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs>
struct Sub : public Expr::Base<Sub<_lhs, _rhs>> {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  const lhs_type _l;
  const rhs_type _r;

  constexpr static size_t rows = lhs_type::rows;  // doesn't matter if it's
  constexpr static size_t cols = rhs_type::cols;  // lhs or rhs, it's equal

  constexpr Sub(const lhs_type& _l, const rhs_type& _r) : _l(_l), _r(_r) {
    static_assert(
        lhs_type::rows == rhs_type::rows && _lhs::cols == rhs_type::cols,
        "Error: dimension mismatch between `lhs_type` and `rhs_type`.");
  }

  /**
   * @brief Computes the element-wise difference at the specified matrix position.
   *
   * @param i Row index.
   * @param j Column index.
   * @return The result of subtracting the right-hand side element from the left-hand side element at position (i, j).
   */
  constexpr auto operator()(size_t i, size_t j) const {
    return _l(i, j) - _r(i, j);
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arithmetic {

template <typename _lhs, typename _rhs>
/**
 * @brief Creates a matrix subtraction expression for two operands.
 *
 * Returns an expression representing the element-wise subtraction of two matrix-like objects with matching dimensions.
 *
 * @return Expression template representing the subtraction of the two operands.
 */
constexpr auto Sub(const _lhs& _l, const _rhs& _r) {
  return Expr::Sub<_lhs, _rhs>(_l, _r);
}

}  // namespace Sglty::Ops::Arithmetic

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
/**
 * @brief Overloads the subtraction operator for matrix-like types.
 *
 * Returns an expression representing the element-wise subtraction of two operands with matching dimensions.
 *
 * @return Expression template representing the subtraction of the two operands.
 */
constexpr auto operator-(const _lhs& _l, const _rhs& _r) {
  return Ops::Arithmetic::Sub(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arithmetic/Sub.hpp