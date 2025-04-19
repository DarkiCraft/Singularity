#ifndef SINGULARITYLIB_MATRIX_STORAGE_CORE_HPP
#define SINGULARITYLIB_MATRIX_STORAGE_CORE_HPP

#include <type_traits>

#include "StorageTraits.hpp"
#include "TypeTraits.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename, typename = void>
struct is_valid_storage_implementation : std::false_type {};

template <typename _storage_impl>
struct is_valid_storage_implementation<
    _storage_impl,
    std::void_t<typename _storage_impl::type_traits,
                typename _storage_impl::value_type,
                typename _storage_impl::allocator_type,
                typename _storage_impl::reference,
                typename _storage_impl::const_reference,
                typename _storage_impl::pointer,
                typename _storage_impl::const_pointer,
                decltype(_storage_impl::Rows()),
                decltype(_storage_impl::Cols()),
                typename _storage_impl::storage_traits,
                decltype(_storage_impl::StorageType()),
                decltype(_storage_impl::StorageMode()),
                decltype(_storage_impl::StorageOrdr()),
                decltype(std::declval<_storage_impl&>().At(
                    std::declval<size_t>(), std::declval<size_t>())),
                decltype(std::declval<const _storage_impl&>().At(
                    std::declval<size_t>(), std::declval<size_t>())),
                decltype(std::declval<_storage_impl&>().Data()),
                decltype(std::declval<const _storage_impl&>().Data())>>
    : std::true_type {};

template <typename _storage_impl>
constexpr bool is_valid_storage_implementation_v =
    is_valid_storage_implementation<_storage_impl>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_STORAGE_CORE_HPP

// SingularityLib/Matrix/StorageCore.hpp