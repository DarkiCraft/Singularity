#ifndef SINGULARITY_ARITHMETIC_MUL_HPP
#define SINGULARITY_ARITHMETIC_MUL_HPP

#include <type_traits>

#include "../Expr/Arithmetic/Mul.hpp"
#include "../Traits/Expr.hpp"

namespace Sglty {

namespace Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        Expr::MulScalar<_lhs, _rhs> > {
  return Expr::MulScalar<_lhs, _rhs>(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        Expr::MulScalar<_rhs, _lhs> > {
  return Expr::MulScalar<_rhs, _lhs>(_r, _l);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            Sglty::is_expression_v<_rhs>,
                        Expr::MulMatrix<_lhs, _rhs> > {
  return Expr::MulMatrix<_lhs, _rhs>(_l, _r);
}

}  // namespace Arthm

template <typename _lhs, typename _rhs>
constexpr auto operator*(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> ||
                            Sglty::is_expression_v<_rhs>,
                        decltype(Arthm::Mul(_l, _r))> {
  return Arthm::Mul(_l, _r);
}

}  // namespace Sglty

#endif  // SINGULARITY_ARITHMETIC_MUL_HPP

// Singularity/Arithmetic/Mul.hpp