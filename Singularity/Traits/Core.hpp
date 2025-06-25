#pragma once

#include <cstddef>
#include <type_traits>

#include "../Core/Enums.hpp"

namespace Sglty::Traits {

template <Sglty::Core::Mode _core_mode, Sglty::Core::Major _core_major>
struct Core {
  static constexpr Sglty::Core::Mode core_mode   = _core_mode;
  static constexpr Sglty::Core::Major core_major = _core_major;
};

template <typename, typename = void>
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

// Singularity/Traits/Core.hpp
