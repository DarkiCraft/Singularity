#ifndef SINGULARITY_ARITHMETIC_EXPR_ADD_HPP
#define SINGULARITY_ARITHMETIC_EXPR_ADD_HPP

#include <cstddef>

#include "../../Expr/Base.hpp"

using std::size_t;

namespace Sglty {

template <typename _lhs, typename _rhs>
struct ExprAdd : public ExprBase<ExprAdd<_lhs, _rhs>> {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  const lhs_type& _l;
  const rhs_type& _r;

  constexpr static size_t rows = lhs_type::rows;  // doesn't matter if it's
  constexpr static size_t cols = rhs_type::cols;  // lhs or rhs, it's equal

  constexpr ExprAdd(const lhs_type& _l, const rhs_type& _r) : _l(_l), _r(_r) {
    static_assert(
        lhs_type::rows == rhs_type::rows && _lhs::cols == rhs_type::cols,
        "Error: dimension mismatch between `lhs_type` and `rhs_type`.");
  }

  constexpr auto operator()(size_t i, size_t j) const {
    return _l(i, j) + _r(i, j);
  }
};

}  // namespace Sglty

#endif  // SINGULARITY_ARITHMETIC_EXPR_ADD_HPP

// Singularity/Arithmetic/Expr/Add.hpp