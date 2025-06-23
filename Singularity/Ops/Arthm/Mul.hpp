#pragma once

#include <string>
#include <type_traits>

#include "../../Expr/Base.hpp"
#include "../../Traits/Expr.hpp"

namespace Sglty::Expr {

struct MulScalar {
  template <typename _lhs, typename _rhs>
  constexpr static size_t rows = _lhs::rows;

  template <typename _lhs, typename _rhs>
  constexpr static size_t cols = _lhs::cols;

  template <typename _lhs, typename _rhs>
  using core_type = typename _lhs::core_type;

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            size_t i,
                            size_t j) const {
    return _l(i, j) * _r;
  }
};

struct MulMatrix {
  template <typename _lhs, typename _rhs>
  constexpr static size_t rows = _lhs::rows;

  template <typename _lhs, typename _rhs>
  constexpr static size_t cols = _rhs::cols;

  template <typename _lhs, typename _rhs>
  using core_type =
      typename _lhs::core_type::template core_rebind<rows<_lhs, _rhs>,
                                                     cols<_lhs, _rhs>>;

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            size_t i,
                            size_t j) const {
    static_assert(_lhs::cols == _rhs::rows,
                  "Error: inner dimensions mismatch.");

    using value_type = decltype(std::declval<const _lhs&>()(0, 0) *
                                std::declval<const _rhs&>()(0, 0));
    value_type sum{};               // default initialize the result type
    size_t inner_dim = _lhs::cols;  // = rhs_type::rows
    for (size_t k = 0; k < inner_dim; k++) {
      sum += _l(i, k) * _r(k, j);
    }
    return sum;
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r) -> std::enable_if_t<
    Sglty::Traits::is_expression_v<_lhs> && std::is_arithmetic_v<_rhs>,
    Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::MulScalar>> {
  return Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::MulScalar>(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r) -> std::enable_if_t<
    Sglty::Traits::is_expression_v<_rhs> && std::is_arithmetic_v<_lhs>,
    Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::MulScalar>> {
  return Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::MulScalar>(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r) -> std::enable_if_t<
    Sglty::Traits::is_expression_v<_lhs> &&
        Sglty::Traits::is_expression_v<_rhs>,
    Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::MulMatrix>> {
  return Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::MulMatrix>(_l, _r);
}

}  // namespace Sglty::Ops::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::Traits::is_expression_v<_lhs> ||
                            Sglty::Traits::is_expression_v<_rhs>,
                        decltype(Ops::Arthm::Mul(_l, _r))> {
  return Ops::Arthm::Mul(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arthm/Mul.hpp