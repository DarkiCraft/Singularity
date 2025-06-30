#pragma once

#include "../Expr.hpp"

#include <type_traits>
#include <cstddef>

namespace Sglty::Expr {

struct Tag;  // forward declaration

}  // namespace Sglty::Expr

namespace Sglty::Traits::Expr {

namespace Impl {

template <typename _expr, typename _enable = void>
struct HasTagBase
    : std::bool_constant<std::is_base_of_v<Sglty::Expr::Tag, _expr>> {};

template <typename _expr, typename _enable = void>
struct HasInterface : std::false_type {};

template <typename _expr>
struct HasInterface<
    _expr,
    std::void_t<decltype(static_cast<std::size_t>(_expr::rows)),
                decltype(static_cast<std::size_t>(_expr::cols)),
                typename _expr::core_impl,
                decltype(std::declval<_expr const&>()(
                    std::declval<std::size_t>(), std::declval<std::size_t>()))

                >> : std::true_type {};

template <typename _expr, typename _enable = void>
struct IsValid : std::conjunction<HasTagBase<_expr>, HasInterface<_expr>> {};

}  // namespace Impl

template <typename _expr>
constexpr inline bool has_tag_base_v = Impl::HasTagBase<_expr>::value;

template <typename _expr>
constexpr inline bool has_interface_v = Impl::HasInterface<_expr>::value;

template <typename _expr>
constexpr inline bool is_valid_v = Impl::IsValid<_expr>::value;

}  // namespace Sglty::Traits::Expr

// Singularity/Traits/Impl/Expr.tpp
