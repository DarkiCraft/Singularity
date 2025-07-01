#pragma once

#include "../Op.hpp"

#include <type_traits>

#include "../../Expr/Dummy.hpp"

namespace Sglty::Traits::Op {

namespace Impl {

template <typename _op, typename _enable = void>
struct IsUnary : std::false_type {};

template <typename _op>
struct IsUnary<
    _op,
    std::void_t<decltype(_op::template rows<Sglty::Expr::Dummy>),
                decltype(_op::template cols<Sglty::Expr::Dummy>),
                typename _op::template core_impl<Sglty::Expr::Dummy>,
                decltype(_op::template is_valid_core_impl<Sglty::Expr::Dummy>),
                decltype(_op::template is_valid_dimension<Sglty::Expr::Dummy>),
                decltype(std::declval<_op>().operator()(
                    std::declval<const Sglty::Expr::Dummy&>(),
                    std::size_t{},
                    std::size_t{}))>> : std::true_type {};

template <typename _op, typename _enable = void>
struct IsBinary : std::false_type {};

template <typename _op>
struct IsBinary<
    _op,
    std::void_t<
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
struct IsValid : std::disjunction<IsUnary<_op>, IsBinary<_op>> {};

}  // namespace Impl

template <typename _op>
constexpr inline bool is_unary_v = Impl::IsUnary<_op>::value;

template <typename _op>
constexpr inline bool is_binary_v = Impl::IsBinary<_op>::value;

template <typename _op>
constexpr inline bool is_valid_v = Impl::IsValid<_op>::value;

}  // namespace Sglty::Traits::Op

// Singularity/Traits/Impl/Op.tpp
