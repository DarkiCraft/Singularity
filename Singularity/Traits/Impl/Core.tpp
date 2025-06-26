#pragma once

#include "../Core.hpp"

#include <type_traits>

namespace Sglty::Traits {

template <typename _core_traits, typename _enable = void>
struct IsValidCore : std::false_type {};

template <typename _core_traits>
struct IsValidCore<_core_traits,
                   std::void_t<decltype(_core_traits::core_mode),
                               decltype(_core_traits::core_major)>>
    : std::bool_constant<
          (_core_traits::core_mode == Sglty::Core::Mode::Dense &&
           (_core_traits::core_major == Sglty::Core::Major::Row ||
            _core_traits::core_major == Sglty::Core::Major::Col)) ||
          _core_traits::core_mode == Sglty::Core::Mode::Sparse> {};

template <typename core_traits>
constexpr bool is_valid_core_v = IsValidCore<core_traits>::value;

}  // namespace Sglty::Traits

// Singularity/Traits/Impl/Core.tpp
