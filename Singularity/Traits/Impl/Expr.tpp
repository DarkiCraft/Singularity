#pragma once

#include "../Expr.hpp"

#include <type_traits>

#include "../../Expr/Dummy.hpp"

namespace Sglty::Traits {

template <typename _expr, typename _enable = void>
struct IsExpression : std::false_type {};

template <typename _expr>
struct IsExpression<_expr,
                    std::enable_if_t<std::is_base_of_v<Expr::Tag, _expr>>> {
 private:
  template <typename T, typename = void>
  struct Check : std::false_type {};

  template <typename T>
  struct Check<T,
               std::void_t<decltype(static_cast<std::size_t>(T::rows)),
                           decltype(static_cast<std::size_t>(T::cols)),
                           typename T::core_type,
                           decltype(std::declval<T const&>()(
                               std::declval<std::size_t>(),
                               std::declval<std::size_t>()))>>
      : std::true_type {};

 public:
  static constexpr bool value = Check<_expr>::value;
};

template <typename _expr>
constexpr bool is_expression_v = IsExpression<_expr>::value;

template <typename _op, typename _enable = void>
struct IsValidOp : std::false_type {};

template <typename _op>
struct IsValidOp<
    _op,
    std::void_t<  // overload for binary ops
        decltype(_op::template rows<Expr::Dummy, Expr::Dummy>),
        decltype(_op::template cols<Expr::Dummy, Expr::Dummy>),
        typename _op::template core_type<Expr::Dummy, Expr::Dummy>,
        decltype(_op::template is_valid_core_type<Expr::Dummy, Expr::Dummy>),
        decltype(_op::template is_valid_dimension<Expr::Dummy, Expr::Dummy>),
        decltype(std::declval<_op>().operator()(
            std::declval<const Expr::Dummy&>(),
            std::declval<const Expr::Dummy&>(),
            std::size_t{},
            std::size_t{}))>> : std::true_type {};

template <typename _op>
struct IsValidOp<
    _op,
    std::void_t<  // overload for unary ops
        decltype(_op::template rows<Expr::Dummy>),
        decltype(_op::template cols<Expr::Dummy>),
        typename _op::template core_type<Expr::Dummy>,
        decltype(_op::template is_valid_core_type<Expr::Dummy>),
        decltype(_op::template is_valid_dimension<Expr::Dummy>),
        decltype(std::declval<_op>().operator()(
            std::declval<const Expr::Dummy&>(), std::size_t{}, std::size_t{}))>>
    : std::true_type {};

template <typename _op>
constexpr bool is_valid_op_v = IsValidOp<_op>::value;

}  // namespace Sglty::Traits

// Singularity/Traits/Impl/Expr.tpp
