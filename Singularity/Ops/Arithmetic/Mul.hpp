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

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arithmetic {

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        Expr::MulScalar<_lhs, _rhs>> {
  return Expr::MulScalar<_lhs, _rhs>(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        Expr::MulScalar<_rhs, _lhs>> {
  return Expr::MulScalar<_rhs, _lhs>(_r, _l);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            Sglty::is_expression_v<_rhs>,
                        Expr::MulMatrix<_lhs, _rhs>> {
  return Expr::MulMatrix<_lhs, _rhs>(_l, _r);
}

}  // namespace Sglty::Ops::Arithmetic

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> ||
                            Sglty::is_expression_v<_rhs>,
                        decltype(Ops::Arithmetic::Mul(_l, _r))> {
  return Ops::Arithmetic::Mul(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arithmetic/Mul.hpp