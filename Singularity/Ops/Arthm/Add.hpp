#pragma once

#include <type_traits>

#include "../../Expr/Binary.hpp"

namespace Sglty::Expr {

struct Add {
  template <typename _lhs, typename _rhs>
  constexpr static size_t rows = _lhs::rows;  // = _rhs::rows

  template <typename _lhs, typename _rhs>
  constexpr static size_t cols = _lhs::cols;  // = _rhs::cols

  template <typename _lhs, typename _rhs>
  using core_type = typename _lhs::core_type;  // = _rhs::core_type

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            size_t i,
                            size_t j) const {
    return _l(i, j) + _r(i, j);
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Add(const _lhs& _l, const _rhs& _r) {
  static_assert(
      std::is_same_v<typename _lhs::core_type, typename _rhs::core_type>,
      "Error: core_type mismatch.");

  return Sglty::Expr::Binary<_lhs, _rhs, Sglty::Expr::Add>(_l, _r);
}

}  // namespace Sglty::Ops::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator+(const _lhs& _l, const _rhs& _r) {
  return Ops::Arthm::Add(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arthm/Add.hpp