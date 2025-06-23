#pragma once

#include "../../Expr/Unary.hpp"

namespace Sglty::Expr {

struct Trp {
  template <typename _operand>
  constexpr static size_t rows = _operand::cols;

  template <typename _operand>
  constexpr static size_t cols = _operand::rows;

  template <typename _operand>
  using core_type =
      typename _operand::core_type::template core_rebind<rows<_operand>,
                                                         cols<_operand>>;

  template <typename _operand>
  constexpr auto operator()(const _operand& op, size_t i, size_t j) const {
    return op(j, i);
  }
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Alg {

template <typename _operand>
constexpr auto Trp(const _operand& _o) {
  return Sglty::Expr::Unary<_operand, Sglty::Expr::Trp>(_o);
}

}  // namespace Sglty::Ops::Alg

// Singularity/Ops/Alg/Trp.hpp