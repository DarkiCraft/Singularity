#ifndef SINGULARITY_ARITHMETIC_SUB_HPP
#define SINGULARITY_ARITHMETIC_SUB_HPP

#include "Expr/Sub.hpp"

namespace Sglty {

namespace Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Sub(const _lhs& _l, const _rhs& _r) {
  return ExprSub<_lhs, _rhs>(_l, _r);
}

}  // namespace Arthm

template <typename _lhs, typename _rhs>
constexpr auto operator-(const _lhs& _l, const _rhs& _r) {
  return Arthm::Sub(_l, _r);
}

}  // namespace Sglty

#endif  // SINGULARITY_ARITHMETIC_SUB_HPP

// Singularity/Arithmetic/Sub.hpp