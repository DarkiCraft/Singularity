#pragma once

#include "../../Expr/Unary.hpp"

namespace Sglty::Expr {

struct Neg {
  template <typename _operand>
  constexpr static size_t rows = _operand::rows;

  template <typename _operand>
  constexpr static size_t cols = _operand::cols;

  template <typename _operand>
  using core_type = typename _operand::core_type;

  template <typename _operand>
  constexpr auto operator()(const _operand& op, size_t i, size_t j) const {
    return op(i, j) * -1;
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Alg {

template <typename _operand>
constexpr auto Neg(const _operand& _o) {
  return Sglty::Expr::Unary<_operand, Sglty::Expr::Neg>(_o);
}

}  // namespace Sglty::Ops::Alg

// Singularity/Ops/Alg/Neg.hpp