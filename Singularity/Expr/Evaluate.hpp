#pragma once

#include "../Core/Checks.hpp"
#include "../Traits/Expr.hpp"
#include "../Types/Matrix.hpp"
#include "Base.hpp"

namespace Sglty::Expr {

template <typename _expr>
constexpr auto Evaluate(const _expr& _e) -> std::enable_if_t<
    is_expression_v<_expr>,
    Sglty::Types::Matrix<typename Sglty::Traits::Extract<
        _expr>::template core_rebind<_expr::rows, _expr::cols>>> {
  using core_t =
      typename Sglty::Traits::Extract<_expr>::template core_rebind<_expr::rows,
                                                                   _expr::cols>;
  using ret_type  = Sglty::Types::Matrix<core_t>;
  using size_type = typename ret_type::size_type;

  ret_type result;
  for (size_type i = 0; i < result.Rows(); i++) {
    for (size_type j = 0; j < result.Cols(); j++) {
      result(i, j) = _e(i, j);
    }
  }

  return result;
}

template <typename _core_ret, typename _expr>
constexpr auto Evaluate(const _expr& _e) -> std::enable_if_t<
    Core::is_valid_implementation_v<_core_ret> && Sglty::is_expression_v<_expr>,
    Sglty::Types::Matrix<
        typename _core_ret::template core_rebind<_expr::rows, _expr::cols>>> {
  using core_t =
      typename _core_ret::template core_rebind<_expr::rows, _expr::cols>;
  using ret_type  = Sglty::Types::Matrix<core_t>;
  using size_type = typename ret_type::size_type;

  ret_type result;
  for (size_type i = 0; i < result.Rows(); i++) {
    for (size_type j = 0; j < result.Cols(); j++) {
      result(i, j) = _e(i, j);
    }
  }
  return result;
}

}  // namespace Sglty::Expr

// Singularity/Expr/Evaluator.hpp