#pragma once

#include "../Add.hpp"

#include <type_traits>

#include "../../../Expr/Binary.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs>
constexpr auto Add::operator()(const _lhs& _l,
                               const _rhs& _r,
                               std::size_t i,
                               std::size_t j) const {
  static_assert(is_valid_core_type<_lhs, _rhs>, "Error: core_type mismatch.");
  static_assert(is_valid_dimension<_lhs, _rhs>, "Error: invalid dimensions.");
  return _l(i, j) + _r(i, j);
}

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Add(const _lhs& _l, const _rhs& _r) {
  return Expr::Binary<_lhs, _rhs, Expr::Add>(_l, _r);
}

}  // namespace Sglty::Ops::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator+(const _lhs& _l, const _rhs& _r) {
  return Ops::Arthm::Add(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Ops/Arthm/Impl/Add.hpp
