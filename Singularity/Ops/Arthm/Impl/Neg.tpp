#pragma once

#include "../Neg.hpp"

#include <cstddef>
#include "../../../Expr/Unary.hpp"

namespace Sglty::Expr {

template <typename _operand>
constexpr auto Neg::operator()(const _operand& op,
                               std::size_t i,
                               std::size_t j) const {
  return -op(i, j);
}

}  // namespace Sglty::Expr

namespace Sglty::Ops::Arthm {

template <typename _operand>
constexpr auto Neg(const _operand& _o) {
  return Expr::Unary<_operand, Expr::Neg>(_o);
}

}  // namespace Sglty::Ops::Arthm

namespace Sglty::Types {

template <typename _operand>
constexpr auto operator-(const _operand& _o) {
  return Ops::Arthm::Neg(_o);
}

}  // namespace Sglty::Types

// Singularity/Ops/Alg/Impl/Neg.tpp
