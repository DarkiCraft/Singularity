#pragma once

#include <cstddef>
#include <type_traits>

namespace Sglty::Expr {

struct MulScalar {
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;

  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _lhs::cols;

  template <typename _lhs, typename _rhs>
  using core_impl = typename _lhs::core_impl;

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            std::size_t i,
                            std::size_t j) const;
};

struct MulMatrix {
  template <typename _lhs, typename _rhs>
  constexpr static std::size_t rows = _lhs::rows;

  template <typename _lhs, typename _rhs>
  constexpr static std::size_t cols = _rhs::cols;

  template <typename _lhs, typename _rhs>
  using core_impl =
      typename _lhs::core_impl::template core_rebind<rows<_lhs, _rhs>,
                                                     cols<_lhs, _rhs>>;

  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_core_type = std::is_same_v<
      typename _lhs::core_impl::template core_rebind<rows<_lhs, _rhs>,
                                                     cols<_lhs, _rhs>>,
      typename _rhs::core_impl::template core_rebind<rows<_lhs, _rhs>,
                                                     cols<_lhs, _rhs>>>;

  template <typename _lhs, typename _rhs>
  constexpr static bool is_valid_dimension = (_lhs::cols == _rhs::rows);

  template <typename _lhs, typename _rhs>
  constexpr auto operator()(const _lhs& _l,
                            const _rhs& _r,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Op::Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::is_expression_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        Expr::Binary<_lhs, _rhs, Expr::MulScalar>>;
template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::is_expression_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        Expr::Binary<_rhs, _lhs, Expr::MulScalar>>;

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::is_expression_v<_lhs> &&
                            Traits::is_expression_v<_rhs>,
                        Expr::Binary<_lhs, _rhs, Expr::MulMatrix>>;

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Traits::is_expression_v<_lhs> ||
                            Traits::is_expression_v<_rhs>,
                        decltype(Op::Arthm::Mul(_l, _r))>;

}  // namespace Sglty::Types

#include "Impl/Mul.tpp"

// Singularity/Op/Arthm/Mul.hpp
