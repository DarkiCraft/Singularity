#pragma once

#include <cstddef>

namespace Sglty::Expr {

struct Add {
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;  // = _rhs::rows

  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _lhs::cols;  // = _rhs::cols

  template <typename _lhs, typename _rhs>
  using core_impl = typename _lhs::core_impl;  // = _rhs::core_impl

  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_core_type =
      std::is_same_v<typename _lhs::core_impl, typename _rhs::core_impl>;

  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_dimension =
      (_lhs::rows == _rhs::rows) && (_lhs::cols == _rhs::cols);

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Op::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Add(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator+(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Types

#include "Impl/Add.tpp"

// Singularity/Op/Arthm/Add.hpp
