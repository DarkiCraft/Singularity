#ifndef SINGULARITYLIB_EXPR_EXTRACTOR_HPP
#define SINGULARITYLIB_EXPR_EXTRACTOR_HPP

#include <type_traits>

#include "../Matrix.hpp"
#include "Base.hpp"

namespace Sglty {

struct NoMatrixFound {};

template <typename, typename = void>
struct has_lhs_type : std::false_type {};

template <typename _expr>
struct has_lhs_type<_expr, std::void_t<typename _expr::lhs_type>>
    : std::true_type {};

template <typename _expr>
constexpr bool has_lhs_type_v = has_lhs_type<_expr>::value;

template <typename, typename = void>
struct has_rhs_type : std::false_type {};

template <typename _expr>
struct has_rhs_type<_expr, std::void_t<typename _expr::rhs_type>>
    : std::true_type {};

template <typename _expr>
constexpr bool has_rhs_type_v = has_rhs_type<_expr>::value;

template <typename>
struct is_matrix : std::false_type {};

template <typename _core>
struct is_matrix<Sglty::Matrix<_core>> : std::true_type {};

template <typename _expr>
constexpr bool is_matrix_v = is_matrix<_expr>::value;

template <typename _expr, typename = void>
struct is_expression : std::false_type {};

template <typename _expr>
struct is_expression<
    _expr,
    std::enable_if_t<std::is_base_of_v<ExprBase<_expr>, _expr>>>
    : std::true_type {};

template <typename _expr>
constexpr bool is_expression_v = is_expression<_expr>::value;

#define WE_HERE_DAWG 0

template <typename, typename = void>
struct ExtractorImpl {
  using type = NoMatrixFound;
};

template <typename _core>
struct ExtractorImpl<Sglty::Matrix<_core>, void> {
  using type = _core;
};

template <typename _expr>
struct ExtractorImpl<
    _expr,
    std::enable_if_t<is_expression_v<_expr> &&
                     (has_lhs_type_v<_expr> || has_rhs_type_v<_expr>)>> {
 private:
  using lhs_result = typename ExtractorImpl<typename _expr::lhs_type>::type;

  template <typename U = _expr>
  static constexpr auto get_result() {
    if constexpr (!std::is_same_v<lhs_result, NoMatrixFound>) {
      return lhs_result{};
    } else if constexpr (has_rhs_type_v<U>) {
      using rhs_result = typename ExtractorImpl<typename U::rhs_type>::type;
      return rhs_result{};
    } else {
      return NoMatrixFound{};
    }
  }

 public:
  using type = decltype(get_result());
};

template <typename _expr>
struct Extractor {
  using type = typename ExtractorImpl<_expr>::type;
};

template <typename _expr>
using Extractor_t = typename Extractor<_expr>::type;

}  // namespace Sglty

#endif  // SINGULARITYLIB_EXPR_EXTRACTOR_HPP

// Singularity/Expr/Extractor.hpp
