#ifndef SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP
#define SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP

#include <type_traits>

#include "../Traits/Core.hpp"
#include "../Traits/Type.hpp"

using size_t = unsigned long long;

namespace Sglty {

// template <typename, typename = void>
// struct is_valid_core_implementation : std::false_type {};

// template <typename _core_impl>
// struct is_valid_core_implementation<
//     _core_impl,
//     std::void_t<typename _core_impl::type_traits,
//                 typename _core_impl::value_type,
//                 typename _core_impl::allocator_type,
//                 typename _core_impl::reference,
//                 typename _core_impl::const_reference,
//                 typename _core_impl::pointer,
//                 typename _core_impl::const_pointer,
//                 decltype(_core_impl::Rows()),
//                 decltype(_core_impl::Cols()),
//                 typename _core_impl::core_traits,
//                 decltype(_core_impl::CoreType()),
//                 decltype(_core_impl::CoreMode()),
//                 decltype(_core_impl::CoreOrdr()),
//                 decltype(std::declval<_core_impl&>().At(
//                     std::declval<size_t>(), std::declval<size_t>())),
//                 decltype(std::declval<const _core_impl&>().At(
//                     std::declval<size_t>(), std::declval<size_t>())),
//                 decltype(std::declval<_core_impl&>().Data()),
//                 decltype(std::declval<const _core_impl&>().Data())>>
//     : std::true_type {};

// template <typename _core_impl>
// constexpr bool is_valid_core_implementation_v =
//     is_valid_core_implementation<_core_impl>::value;

template <typename, typename = void>
struct has_type_traits : std::false_type {};

template <typename T>
struct has_type_traits<T,
                       std::void_t<typename T::type_traits,
                                   typename T::value_type,
                                   typename T::allocator_type,
                                   typename T::reference,
                                   typename T::const_reference,
                                   typename T::pointer,
                                   typename T::const_pointer,
                                   typename T::core_traits>> : std::true_type {
};

template <typename, typename = void>
struct has_static_methods : std::false_type {};

template <typename T>
struct has_static_methods<T,
                          std::void_t<decltype(T::Rows()),
                                      decltype(T::Cols()),
                                      decltype(T::CoreType()),
                                      decltype(T::CoreMode()),
                                      decltype(T::CoreOrdr())>>
    : std::true_type {};

template <typename, typename = void>
struct has_member_functions : std::false_type {};

template <typename T>
struct has_member_functions<
    T,
    std::void_t<decltype(std::declval<T&>().At(size_t{}, size_t{})),
                decltype(std::declval<const T&>().At(size_t{}, size_t{})),
                decltype(std::declval<T&>().Data()),
                decltype(std::declval<const T&>().Data())>> : std::true_type {};

template <typename T>
struct is_valid_core_implementation
    : std::conjunction<has_type_traits<T>,
                       has_static_methods<T>,
                       has_member_functions<T>> {};

template <typename T>
constexpr bool is_valid_core_implementation_v =
    is_valid_core_implementation<T>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP

// SingularityLib/Matrix/Core/Checks.hpp