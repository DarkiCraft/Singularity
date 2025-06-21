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

  constexpr auto operator()(size_t i, size_t j) const {
    return _l(i, j) + _r(i, j);
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arithmetic {

template <typename _lhs, typename _rhs>
constexpr auto Add(const _lhs& _l, const _rhs& _r) {
  return Expr::Add<_lhs, _rhs>(_l, _r);
}

}  // namespace Sglty::Ops::Arithmetic

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator+(const _lhs& _l, const _rhs& _r) {
  return Ops::Arithmetic::Add(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arithmetic/Add.hpp