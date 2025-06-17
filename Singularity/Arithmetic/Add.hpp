#ifndef SINGULARITY_ARITHMETIC_ADD_HPP
#define SINGULARITY_ARITHMETIC_ADD_HPP

#include "../Expr/Arithmetic/Add.hpp"

namespace Sglty {

namespace Arthm {

template <typename _lhs, typename _rhs>
constexpr auto Add(const _lhs& _l, const _rhs& _r) {
  return Expr::Add<_lhs, _rhs>(_l, _r);
}

}  // namespace Arthm

template <typename _lhs, typename _rhs>
constexpr auto operator+(const _lhs& _l, const _rhs& _r) {
  return Arthm::Add(_l, _r);
}

}  // namespace Sglty

#endif  // SINGULARITY_ARITHMETIC_ADD_HPP

// Singularity/Arithmetic/Add.hpp