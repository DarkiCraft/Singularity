#pragma once

#include "../../Expr/Base.hpp"

namespace Sglty::Expr {

template <typename _lhs>
struct Trp : public Expr::Base<Trp<_lhs>> {
  using lhs_type = _lhs;

  const lhs_type _l;

  constexpr static size_t rows = lhs_type::cols;
  constexpr static size_t cols = lhs_type::rows;

  constexpr Trp(const lhs_type& _l) : _l(_l) {}

  /**
   * @brief Returns the element at position (j, i) of the underlying expression, effectively transposing the indices.
   *
   * @param i Row index in the transposed expression.
   * @param j Column index in the transposed expression.
   * @return The value at position (i, j) in the transposed expression.
   */
  constexpr auto operator()(size_t i, size_t j) const {
    return _l(j, i);
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Algebra {

template <typename _lhs>
/**
 * @brief Returns a transposed expression of the given operand.
 *
 * Constructs and returns an expression representing the transpose of the input expression.
 *
 * @return An expression representing the transpose of the input.
 */
constexpr auto Trp(const _lhs& _l) {
  return Expr::Trp<_lhs>(_l);
}

}  // namespace Sglty::Ops::Algebra

// Singularity/Ops/Algebra/Trp.hpp