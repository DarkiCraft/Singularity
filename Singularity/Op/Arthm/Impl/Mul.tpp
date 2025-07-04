#pragma once

#include "../Mul.hpp"

#include <type_traits>

#include "../../../Expr/Binary.hpp"
#include "../../../Traits/Expr.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs>
constexpr auto MulScalar::operator()(const _lhs& _l,
                                     const _rhs& _r,
                                     std::size_t i,
                                     std::size_t j) const {
  return _l(i, j) * _r;
}

template <typename _lhs, typename _rhs>
constexpr auto MulMatrix::operator()(const _lhs& _l,
                                     const _rhs& _r,
                                     std::size_t i,
                                     std::size_t j) const {
  static_assert(is_valid_core_impl<_lhs, _rhs>,
                "Error: `_lhs` and `_rhs` have different `core_impl` types.");
  static_assert(is_valid_dimension<_lhs, _rhs>,
                "Error: `_lhs` and `_rhs` have incompatible dimensions.");

  using value_type = decltype(std::declval<const _lhs&>()(0, 0) *
                              std::declval<const _rhs&>()(0, 0));
  using value_type = decltype(std::declval<const _lhs&>()(0, 0) *
                              std::declval<const _rhs&>()(0, 0));

  std::size_t inner_dim = _lhs::cols;  // = rhs_type::rows
  value_type sum        = _l(i, 0) * _r(0, j);
  for (std::size_t k = 1; k < inner_dim; k++) {
    sum += _l(i, k) * _r(k, j);
  }
  return sum;
}

}  // namespace Sglty::Expr

namespace Sglty::Op::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        Expr::Binary<_lhs, _rhs, Expr::MulScalar>> {
  return Expr::Binary<_lhs, _rhs, Expr::MulScalar>(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        Expr::Binary<_rhs, _lhs, Expr::MulScalar>> {
  return Expr::Binary<_rhs, _lhs, Expr::MulScalar>(_r, _l);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_lhs> &&
                            Traits::Expr::is_valid_v<_rhs>,
                        Expr::Binary<_lhs, _rhs, Expr::MulMatrix>> {
  return Expr::Binary<_lhs, _rhs, Expr::MulMatrix>(_l, _r);
}

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::Expr::is_valid_v<_lhs> ||
                            Traits::Expr::is_valid_v<_rhs>,
                        decltype(Op::Arthm::Mul(_l, _r))> {
  return Op::Arthm::Mul(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Op/Arthm/Impl/Mul.hpp
