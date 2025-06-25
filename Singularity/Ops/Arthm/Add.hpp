#pragma once

#include <cstddef>
#include <type_traits>

#include "../../Expr/Binary.hpp"

namespace Sglty::Expr {

struct Add {
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;  // = _rhs::rows

  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _lhs::cols;  // = _rhs::cols

  template <typename _lhs, typename _rhs>
  using core_type = typename _lhs::core_type;  // = _rhs::core_type

  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_core_type =
      std::is_same_v<typename _lhs::core_type, typename _rhs::core_type>;

  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_dimension =
      (_lhs::rows == _rhs::rows) && (_lhs::cols == _rhs::cols);

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            std::size_t i,
                            std::size_t j) const {
    static_assert(is_valid_core_type<_lhs, _rhs>, "Error: core_type mismatch.");
    static_assert(is_valid_dimension<_lhs, _rhs>, "Error: invalid dimensions.");
    return _l(i, j) + _r(i, j);
  }
};

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

// Singularity/Ops/Arthm/Add.hpp
