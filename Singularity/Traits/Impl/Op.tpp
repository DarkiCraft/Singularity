#pragma once

#include "../Op.hpp"

#include <type_traits>

#include "../../Expr/Dummy.hpp"

namespace Sglty::Traits::Op {

namespace Impl {

template <typename _op, typename _enable = void>
struct IsValid : std::false_type {};

template <typename _op>
struct IsValid<
    _op,
    std::void_t<  // overload for binary op
        decltype(_op::template rows<Sglty::Expr::Dummy, Sglty::Expr::Dummy>),
        decltype(_op::template cols<Sglty::Expr::Dummy, Sglty::Expr::Dummy>),
        typename _op::template core_impl<Sglty::Expr::Dummy,
                                         Sglty::Expr::Dummy>,
        decltype(_op::template is_valid_core_impl<Sglty::Expr::Dummy,
                                                  Sglty::Expr::Dummy>),
        decltype(_op::template is_valid_dimension<Sglty::Expr::Dummy,
                                                  Sglty::Expr::Dummy>),
        decltype(std::declval<_op>().operator()(
            std::declval<const Sglty::Expr::Dummy&>(),
            std::declval<const Sglty::Expr::Dummy&>(),
            std::size_t{},
            std::size_t{}))>> : std::true_type {};

template <typename _op>
struct IsValid<
    _op,
    std::void_t<  // overload for unary op
        decltype(_op::template rows<Sglty::Expr::Dummy>),
        decltype(_op::template cols<Sglty::Expr::Dummy>),
        typename _op::template core_impl<Sglty::Expr::Dummy>,
        decltype(_op::template is_valid_core_impl<Sglty::Expr::Dummy>),
        decltype(_op::template is_valid_dimension<Sglty::Expr::Dummy>),
        decltype(std::declval<_op>().operator()(
            std::declval<const Sglty::Expr::Dummy&>(),
            std::size_t{},
            std::size_t{}))>> : std::true_type {};
}  // namespace Impl

template <typename _op>
constexpr inline bool is_valid_v = Impl::IsValid<_op>::value;

}  // namespace Sglty::Traits::Op

// Singularity/Traits/Impl/Op.tpp
