#pragma once

#include "../Eql.hpp"

#include <cstddef>

namespace Sglty::Op::Cmp {

template <typename _lhs, typename _rhs>
constexpr bool IsEqual(const _lhs& _l, const _rhs& _r) {
  static_assert(_lhs::rows == _rhs::rows && _lhs::cols == _rhs::cols,
                "Error: dimension mismatch.");
  for (std::size_t i = 0; i < _lhs::rows; i++) {
    for (std::size_t j = 0; j < _lhs::cols; j++) {
      if (_l(i, j) != _r(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <typename _lhs, typename _rhs>
constexpr bool IsNotEqual(const _lhs& _l, const _rhs& _r) {
  return !IsEqual(_l, _r);
}

}  // namespace Sglty::Op::Cmp

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr bool operator==(const _lhs& _l, const _rhs& _r) {
  return Op::Cmp::IsEqual(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr bool operator!=(const _lhs& _l, const _rhs& _r) {
  return Op::Cmp::IsNotEqual(_l, _r);
}

}  // namespace Sglty::Types

// Singularity/Op/Cmp/Impl/Eql.tpp
