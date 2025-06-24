#pragma once

#include <cstddef>
#include <type_traits>

#include "../Expr/Base.hpp"
#include "Core.hpp"

namespace Sglty::Traits {

template <typename _expr, typename = void>
struct IsExpression : std::false_type {};

template <typename _expr>
struct IsExpression<
    _expr,
    std::enable_if_t<std::is_base_of_v<Expr::Base<_expr>, _expr>>>
    : std::true_type {};

template <typename _expr>
constexpr bool is_expression_v = IsExpression<_expr>::value;

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

struct DummyExpr {
  static constexpr size_t rows = 0;
  static constexpr size_t cols = 0;

  using core_type = Traits::DummyCore;

  constexpr int operator()(size_t, size_t) const {
    return 0;
  }
};

struct DummyOp {
  template <typename, typename>
  static constexpr size_t rows = 0;

  template <typename, typename>
  static constexpr size_t cols = 0;

  template <typename, typename>
  using core_type = Traits::DummyCore;

  template <typename, typename>
  constexpr static bool is_valid_core_types = true;

  template <typename, typename>
  constexpr static bool is_valid_dimensions = true;

  template <typename, typename>
  constexpr int operator()(std::size_t, std::size_t) const {
    return 0;
  }
};

template <typename _op, typename = void>
struct IsValidOp : std::false_type {};

template <typename _op>
struct IsValidOp<
    _op,
    std::void_t<  // overload for unary ops
        decltype(_op::template rows<DummyExpr, DummyExpr>),
        decltype(_op::template cols<DummyExpr, DummyExpr>),
        typename _op::template core_type<DummyExpr, DummyExpr>,
        decltype(_op::template is_valid_core_types<DummyExpr, DummyExpr>),
        decltype(_op::template is_valid_dimensions<DummyExpr, DummyExpr>),
        decltype(std::declval<_op>().operator()(
            std::declval<const DummyExpr&>(),
            std::declval<const DummyExpr&>(),
            std::size_t{},
            std::size_t{}))>> : std::true_type {};

template <typename _op>
struct IsValidOp<
    _op,
    std::void_t<  // overload for binary ops
        decltype(_op::template rows<DummyExpr>),
        decltype(_op::template cols<DummyExpr>),
        typename _op::template core_type<DummyExpr>,
        decltype(_op::template is_valid_core_types<DummyExpr>),
        decltype(_op::template is_valid_dimensions<DummyExpr>),
        decltype(std::declval<_op>().operator()(
            std::declval<const DummyExpr&>(), std::size_t{}, std::size_t{}))>>
    : std::true_type {};

template <typename _op>
constexpr bool is_valid_op_v = IsValidOp<_op>::value;

}  // namespace Sglty::Traits

// Singularity/Traits/Expr.hpp