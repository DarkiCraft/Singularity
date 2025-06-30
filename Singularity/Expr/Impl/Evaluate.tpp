#pragma once

#include "../Evaluate.hpp"

#include "../../Traits/Expr.hpp"
#include "../../Types/Matrix.hpp"

namespace Sglty::Expr {

template <typename _expr>
constexpr auto Evaluate(const _expr& _e) {
  static_assert(Traits::Expr::is_valid_v<_expr>,
                "Error: `_expr` is not a valid expression type.");

  Types::Matrix<typename _expr::core_impl> ret(0);
  Traverse(ret, [&](std::size_t i, std::size_t j) { ret(i, j) = _e(i, j); });

  return ret;
}

}  // namespace Sglty::Expr

// Singularity/Expr/Impl/Evaluate.tpp
