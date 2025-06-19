#ifndef SINGULARITY_ARITHMETIC_EXPR_MUL_HPP
#define SINGULARITY_ARITHMETIC_EXPR_MUL_HPP

#include "../Base.hpp"

namespace Sglty {

namespace Expr {

template <typename _lhs, typename _rhs>
struct MulScalar : public Expr::Base<MulScalar<_lhs, _rhs>> {
  using lhs_type = _lhs;  // expression
  using rhs_type = _rhs;  // scalar

  const lhs_type _l;
  const rhs_type _r;

  constexpr static size_t rows = lhs_type::rows;  // doesn't matter if it's
  constexpr static size_t cols = lhs_type::cols;  // lhs or rhs, it's equal

  constexpr MulScalar(const lhs_type& _l, const rhs_type& _r)
      : _l(_l), _r(_r) {}

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

  constexpr MulMatrix(const lhs_type& _l, const rhs_type& _r)
      : _l(_l), _r(_r) {}

  constexpr auto operator()(size_t i, size_t j) const {
    decltype(_l(0, 0) * _r(0, 0)) sum{};  // default initialize the result type
    size_t inner_dim = lhs_type::cols;    // = rhs_type::rows
    for (size_t k = 0; k < inner_dim; k++) {
      sum += _l(i, k) * _r(k, j);
    }
    return sum;
  }
};

}  // namespace Expr

}  // namespace Sglty

#endif  // SINGULARITY_ARITHMETIC_EXPR_MUL_HPP

// Singularity/Arithmetic/Expr/Mul.hpp