#ifndef SINGULARITYLIB_EXPR_EVALUATOR_HPP
#define SINGULARITYLIB_EXPR_EVALUATOR_HPP

#include "../Matrix.hpp"
#include "Base.hpp"
#include "Extractor.hpp"

namespace Sglty {

// template <typename _expr>
// auto EvaluateExpr(const _expr& _e)
//     -> std::enable_if_t<is_expression_v<_expr>, Matrix<Extractor_t<_expr>>> {
//   using ret_type  = Matrix<Extractor_t<_expr>>;
//   using size_type = typename ret_type::size_type;

//   ret_type result;
//   for (size_type i = 0; i < result.Rows(); i++) {
//     for (size_type j = 0; j < result.Cols(); j++) {
//       result(i, j) = _e(i, j);
//     }
//   }
//   return result;
// }

template <typename _expr>
auto EvaluateExpr(const _expr& _e) -> std::enable_if_t<
    is_expression_v<_expr>,
    Matrix<typename Extractor_t<_expr>::template core_rebind<_expr::rows,
                                                             _expr::cols>>> {
  using core_t = typename Extractor_t<_expr>::template core_rebind<_expr::rows,
                                                                   _expr::cols>;
  using ret_type  = Matrix<core_t>;
  using size_type = typename ret_type::size_type;

  ret_type result;
  for (size_type i = 0; i < result.Rows(); ++i)
    for (size_type j = 0; j < result.Cols(); ++j) result(i, j) = _e(i, j);

  return result;
}

// template <typename _core_ret, typename _expr>
// auto EvaluateExpr(const _expr& _e)
//     -> std::enable_if_t<is_valid_core_implementation_v<_core_ret> &&
//                             is_expression_v<_expr>,
//                         Matrix<_core_ret>> {
//   using ret_type  = Matrix<_core_ret>;
//   using size_type = typename ret_type::size_type;

//   ret_type result;
//   for (size_type i = 0; i < result.Rows(); i++) {
//     for (size_type j = 0; j < result.Cols(); j++) {
//       result(i, j) = _e(i, j);
//     }
//   }
//   return result;
// }

template <typename _core_ret, typename _expr>
auto EvaluateExpr(const _expr& _e) -> std::enable_if_t<
    is_valid_core_implementation_v<_core_ret> && is_expression_v<_expr>,
    Matrix<
        typename _core_ret::template core_rebind<_expr::rows, _expr::cols>>> {
  using core_t =
      typename _core_ret::template core_rebind<_expr::rows, _expr::cols>;
  using ret_type  = Matrix<core_t>;
  using size_type = typename ret_type::size_type;

  ret_type result;
  for (size_type i = 0; i < result.Rows(); ++i)
    for (size_type j = 0; j < result.Cols(); ++j) result(i, j) = _e(i, j);

  return result;
}

}  // namespace Sglty

#endif  // SINGULARITYLIB_EXPR_EVALUATOR_HPP

// Singularity/Expr/Evaluator.hpp