#pragma once

#include "../Traits/Expr.hpp"
#include "../Types/Matrix.hpp"

namespace Sglty::Expr {

template <typename _expr,
          bool _enable = Traits::is_expression_v<_expr>,
          typename     = std::enable_if_t<_enable>>
constexpr auto Evaluate(const _expr& _e) {
  Sglty::Types::Matrix<typename _expr::core_type> ret;
  ret.TraverseIndices([&](size_t i, size_t j) { ret(i, j) = _e(i, j); });

  return ret;
}

}  // namespace Sglty::Expr

// Singularity/Expr/Evaluator.hpp