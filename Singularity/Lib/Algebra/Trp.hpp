#ifndef SINGULARITY_ALGEBRA_TRP_HPP
#define SINGULARITY_ALGEBRA_TRP_HPP

#include "../Expr/Algebra/Trp.hpp"

namespace Sglty {

namespace Alg {

template <typename _lhs>
constexpr auto Trp(const _lhs& _l) {
  return Expr::Trp<_lhs>(_l);
}

}  // namespace Alg

}  // namespace Sglty

#endif  // SINGULARITY_ALGEBRA_TRP_HPP

// Singularity/Algebra/Trp.hpp