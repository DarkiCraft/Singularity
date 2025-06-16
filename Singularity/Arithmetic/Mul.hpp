#ifndef SINGULARITY_ARITHMETIC_MUL_HPP
#define SINGULARITY_ARITHMETIC_MUL_HPP

#include <type_traits>

#include "../Expr/Extractor.hpp"
#include "Expr/Mul.hpp"

namespace Sglty {

namespace Arthm {

// template <typename _lhs,
//           typename _rhs,
//           typename = std::enable_if_t<Sglty::is_expression_v<_lhs> &&
//                                       std::is_arithmetic_v<_rhs>>>
// constexpr auto Mul(const _lhs& _l, const _rhs& _r) {
//   return ExprMulScalar<_lhs, _rhs>(_l, _r);
// }

// template <typename _lhs,
//           typename _rhs,
//           typename = std::enable_if_t<Sglty::is_expression_v<_rhs> &&
//                                       std::is_arithmetic_v<_lhs>>>
// constexpr auto Mul(const _lhs& _l, const _rhs& _r) {
//   return ExprMul<_rhs, _lhs>(_r, _l);
// }

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            std::is_arithmetic_v<_rhs>,
                        ExprMulScalar<_lhs, _rhs> > {
  return ExprMulScalar<_lhs, _rhs>(_l, _r);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_rhs> &&
                            std::is_arithmetic_v<_lhs>,
                        ExprMulScalar<_rhs, _lhs> > {
  return ExprMulScalar<_rhs, _lhs>(_r, _l);
}

template <typename _lhs, typename _rhs>
constexpr auto Mul(const _lhs& _l, const _rhs& _r)
    -> std::enable_if_t<Sglty::is_expression_v<_lhs> &&
                            Sglty::is_expression_v<_rhs>,
                        ExprMulMatrix<_lhs, _rhs> > {
  return ExprMulMatrix<_lhs, _rhs>(_l, _r);
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