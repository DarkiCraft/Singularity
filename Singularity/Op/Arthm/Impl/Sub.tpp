#pragma once

#include "../Sub.hpp"

#include <type_traits>

#include "../../../Expr/Binary.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs>
constexpr auto Sub::operator()(const _lhs& _l,
                               const _rhs& _r,
                               std::size_t i,
                               std::size_t j) const {
  static_assert(is_valid_core_type<_lhs, _rhs>, "Error: core_impl mismatch.");
  static_assert(is_valid_dimension<_lhs, _rhs>, "Error: invalid dimensions.");
  return _l(i, j) - _r(i, j);
}

}  // namespace Sglty::Expr

namespace Sglty::Op::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Sub(const _lhs& _l, const _rhs& _r) {
  return Expr::Binary<_lhs, _rhs, Expr::Add>(_l, _r);
}

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator-(const _lhs& _l, const _rhs& _r) {
  return Op::Arthm::Sub(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Op/Arthm/Impl/Sub.hpp
