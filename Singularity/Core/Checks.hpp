#pragma once

#include <cstddef>
#include <type_traits>

#include "../Traits/Core.hpp"
#include "../Traits/Size.hpp"
#include "../Traits/Type.hpp"

namespace Sglty::Core {

template <typename, typename _enable = void>
struct HasSizeTraits : std::false_type {};

template <typename _core_impl>
struct HasSizeTraits<
    _core_impl,
    std::enable_if_t<
        std::is_integral_v<decltype(_core_impl::size_traits::rows)> &&
        std::is_integral_v<decltype(_core_impl::size_traits::cols)>>>
    : std::true_type {};

template <typename _core_impl>
constexpr bool has_size_traits_v = HasSizeTraits<_core_impl>::value;

template <typename, typename _enable = void>
struct HasTypeTraits : std::false_type {};

template <typename _core_impl>
struct HasTypeTraits<
    _core_impl,
    std::void_t<typename _core_impl::type_traits,
                typename _core_impl::type_traits::size_type,
                typename _core_impl::type_traits::value_type,
                typename _core_impl::type_traits::difference_type,
                typename _core_impl::type_traits::reference,
                typename _core_impl::type_traits::const_reference,
                typename _core_impl::type_traits::pointer,
                typename _core_impl::type_traits::const_pointer>>
    : std::true_type {};

template <typename _core_impl>
constexpr bool has_type_traits_v = HasTypeTraits<_core_impl>::value;

template <typename, typename _enable = void>
struct HasCoreTraits : std::false_type {};

template <typename _core_impl>
struct HasCoreTraits<
    _core_impl,
    std::enable_if_t<
        std::is_same_v<decltype(_core_impl::core_traits::core_mode),
                       const Core::Mode> &&
        std::is_same_v<decltype(_core_impl::core_traits::core_order),
                       const Core::Order>>> : std::true_type {};

template <typename _core_impl>
constexpr bool has_core_traits_v = HasCoreTraits<_core_impl>::value;

template <typename _core_impl, typename _enable = void>
struct IsRebindable : std::false_type {};

template <typename _core_impl>
struct IsRebindable<
    _core_impl,
    std::void_t<typename _core_impl::core_base,
                decltype(std::declval<
                         typename _core_impl::template core_rebind<0, 0>>())>>
    : std::bool_constant<
          std::is_same_v<typename _core_impl::core_base,
                         typename _core_impl::template core_rebind<0, 0>>> {};

template <typename _core_impl>
constexpr bool is_rebindable_v = IsRebindable<_core_impl>::value;

template <typename _core_impl, typename _enable = void>
struct HasMemberFunctions : std::false_type {};

template <typename _core_impl>
struct HasMemberFunctions<
    _core_impl,
    std::void_t<HasTypeTraits<_core_impl>,
                decltype(std::declval<_core_impl&>().At(std::size_t{},
                                                        std::size_t{})),
                decltype(std::declval<const _core_impl&>().At(std::size_t{},
                                                              std::size_t{})),
                decltype(std::declval<_core_impl&>().Data()),
                decltype(std::declval<const _core_impl&>().Data())>> {
 private:
  using type_traits = typename _core_impl::type_traits;

  using value_type      = typename type_traits::value_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  static constexpr bool _m_At_nonconst_returns_ref =
      std::is_same_v<decltype(std::declval<_core_impl&>().At(std::size_t{},
                                                             std::size_t{})),
                     reference>;

  static constexpr bool _m_At_const_returns_cref =
      std::is_same_v<decltype(std::declval<const _core_impl&>().At(
                         std::size_t{}, std::size_t{})),
                     const_reference>;

  static constexpr bool _m_Data_nonconst_returns_ptr =
      std::is_same_v<decltype(std::declval<_core_impl&>().Data()), pointer>;

  static constexpr bool _m_Data_const_returns_cptr =
      std::is_same_v<decltype(std::declval<const _core_impl&>().Data()),
                     const_pointer>;

 public:
  static constexpr bool value =
      _m_At_nonconst_returns_ref && _m_At_const_returns_cref &&
      _m_Data_nonconst_returns_ptr && _m_Data_const_returns_cptr;
};

template <typename _core_impl>
constexpr bool has_member_functions_v = HasMemberFunctions<_core_impl>::value;

template <typename _core_impl>
struct IsValidImplementation
    : std::conjunction<HasSizeTraits<_core_impl>,
                       HasTypeTraits<_core_impl>,
                       HasCoreTraits<_core_impl>,
                       IsRebindable<_core_impl>,
                       HasMemberFunctions<_core_impl>> {};

template <typename _core_impl>
constexpr bool is_valid_implementation_v =
    IsValidImplementation<_core_impl>::value;

}  // namespace Sglty::Core

// Singularity/Core/Checks.hpp
