#pragma once

#include "../Trp.hpp"

#include <cstddef>
#include "../../../Expr/Unary.hpp"

namespace Sglty::Expr {

template <typename _operand>
constexpr auto Trp::operator()(const _operand& op,
                               std::size_t i,
                               std::size_t j) const {
  return op(j, i);
}

}  // namespace Sglty::Expr

namespace Sglty::Op::Alg {

template <typename _operand>
constexpr auto Trp(const _operand& _o) {
  return Expr::Unary<_operand, Expr::Trp>(_o);
}

}  // namespace Sglty::Op::Alg

// Singularity/Op/Alg/Impl/Trp.tpp
