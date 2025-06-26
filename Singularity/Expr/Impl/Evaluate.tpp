#pragma once

#include "../Evaluate.hpp"

#include "../../Traits/Expr.hpp"
#include "../../Types/Matrix.hpp"

namespace Sglty::Expr {

template <typename _expr>
constexpr auto Evaluate(const _expr& _e) {
  static_assert(Traits::is_expression_v<_expr>,
                "Error: _expr is not an expression.");

  Types::Matrix<typename _expr::core_impl> ret(0);
  ret.TraverseIndices(
      [&](std::size_t i, std::size_t j) { ret(i, j) = _e(i, j); });

  return ret;
}

}  // namespace Sglty::Expr

// Singularity/Expr/Impl/Evaluate.tpp
