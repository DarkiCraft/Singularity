#pragma once

#include "../Unary.hpp"

namespace Sglty::Expr {

template <typename _operand, typename _op>
constexpr Unary<_operand, _op>::Unary(const operand_type& _o) : _o(_o) {}

template <typename _operand, typename _op>
constexpr auto Unary<_operand, _op>::operator()(std::size_t i,
                                                std::size_t j) const {
  return op_type{}(_o, i, j);
}

}  // namespace Sglty::Expr

// Singularity/Expr/Impl/Unary.tpp
