#pragma once

#include <type_traits>

#include "../Expr/Base.hpp"
// #include "../Matrix.hpp" // this breaks, using forward declaration for now

namespace Sglty {

template <typename _expr, typename = void>
struct IsExpression : std::false_type {};

template <typename _expr>
struct IsExpression<
    _expr,
    std::enable_if_t<std::is_base_of_v<Expr::Base<_expr>, _expr>>>
    : std::true_type {};

template <typename _expr>
constexpr bool is_expression_v = IsExpression<_expr>::value;

}  // namespace Sglty

namespace Sglty::Types {

template <typename>
class Matrix;  // forward declaration

}  // namespace Sglty::Types

namespace Sglty::Traits {

template <typename, typename = void>
struct HasLHSType : std::false_type {};

template <typename _expr>
struct HasLHSType<_expr, std::void_t<typename _expr::lhs_type>>
    : std::true_type {};

template <typename _expr>
constexpr bool has_lhs_type_v = HasLHSType<_expr>::value;

template <typename, typename = void>
struct HasRHSType : std::false_type {};

template <typename _expr>
struct HasRHSType<_expr, std::void_t<typename _expr::rhs_type>>
    : std::true_type {};

template <typename _expr>
constexpr bool has_rhs_type_v = HasRHSType<_expr>::value;

struct NoMatrixFound {};

template <typename, typename = void>
struct ExtractImpl {
  using type = NoMatrixFound;
};

template <typename _core>
struct ExtractImpl<Sglty::Types::Matrix<_core>, void> {
  using type = _core;
};

template <typename _expr>
struct ExtractImpl<_expr,
                   std::enable_if_t<Sglty::is_expression_v<_expr> &&
                                    (Sglty::Traits::has_lhs_type_v<_expr> ||
                                     Sglty::Traits::has_rhs_type_v<_expr>)>> {
 private:
  using lhs_result = typename ExtractImpl<typename _expr::lhs_type>::type;

  template <typename U = _expr>
  static constexpr auto get_result() {
    if constexpr (!std::is_same_v<lhs_result, NoMatrixFound>) {
      return lhs_result{};
    } else if constexpr (Traits::has_rhs_type_v<U>) {
      using rhs_result = typename ExtractImpl<typename U::rhs_type>::type;
      return rhs_result{};
    } else {
      return NoMatrixFound{};
    }
  }

 public:
  using type = decltype(get_result());
};

template <typename _expr>
using Extract = typename ExtractImpl<_expr>::type;

}  // namespace Sglty::Traits

// Singularity/Traits/Expr.hpp