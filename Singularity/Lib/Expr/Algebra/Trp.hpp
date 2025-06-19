#ifndef SINGULARITY_ALGEBRA_EXPR_TRP_HPP
#define SINGULARITY_ALGEBRA_EXPR_TRP_HPP

#include <cstddef>

#include "../Base.hpp"

namespace Sglty {

using std::size_t;

namespace Expr {

template <typename _lhs>
struct Trp : public Expr::Base<Trp<_lhs>> {
  using lhs_type = _lhs;

  const lhs_type _l;

  constexpr static size_t rows = lhs_type::cols;
  constexpr static size_t cols = lhs_type::rows;

  constexpr Trp(const lhs_type& _l) : _l(_l) {}

  constexpr auto operator()(size_t i, size_t j) const {
    return _l(j, i);
  }
};

}  // namespace Expr

}  // namespace Sglty

#endif  // SINGULARITY_ALGEBRA_EXPR_TRP_HPP

// Singularity/Algebra/Expr/Trp.hpp