#pragma once

#include "Base.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs, typename _op>
struct Binary : Base<Binary<_lhs, _rhs, _op>> {
  using lhs_type = _lhs;
  using rhs_type = _rhs;
  using op_type  = _op;

  using core_type = typename op_type::core_type<lhs_type, rhs_type>;

  // static_assert(std::is_same_v<typename lhs_type::core_type,
  //                              typename rhs_type::core_type>,
  //               "Error: Mismatch between core types.");

  constexpr Binary(const lhs_type& _l, const rhs_type& _r) : _l(_l), _r(_r) {}

  constexpr auto operator()(size_t i, size_t j) const {
    return op_type{}(_l, _r, i, j);
  }

  constexpr static size_t rows = op_type::template rows<lhs_type, rhs_type>;
  constexpr static size_t cols = op_type::template cols<lhs_type, rhs_type>;

  const lhs_type _l;
  const rhs_type _r;
};

}  // namespace Sglty::Expr

// Singularity/Expr/Binary.hpp