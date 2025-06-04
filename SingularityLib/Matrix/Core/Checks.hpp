#ifndef SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP
#define SINGULARITYLIB_MATRIX_CORE_CHECKS_HPP

#include <type_traits>

#include "../Traits/Core.hpp"
#include "../Traits/Type.hpp"

using size_t = unsigned long long;

namespace Sglty {

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
                          std::void_t<decltype(T::Rows()), decltype(T::Cols())>>
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