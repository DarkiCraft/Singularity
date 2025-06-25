#pragma once

#include "../Binary.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs, typename _op>
constexpr Binary<_lhs, _rhs, _op>::Binary(const lhs_type& _l,
                                          const rhs_type& _r)
    : _l(_l), _r(_r) {}

template <typename _lhs, typename _rhs, typename _op>
constexpr auto Binary<_lhs, _rhs, _op>::operator()(std::size_t i,
                                                   std::size_t j) const {
  return op_type{}(_l, _r, i, j);
}

}  // namespace Sglty::Expr

// Singularity/Expr/Impl/Binary.tpp
