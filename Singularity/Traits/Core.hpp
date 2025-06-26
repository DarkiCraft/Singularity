#pragma once

#include "../Core/Enums.hpp"

namespace Sglty::Traits {

template <Sglty::Core::Type _core_type, Sglty::Core::Major _core_major>
struct Core {
  static constexpr Sglty::Core::Type core_type   = _core_type;
  static constexpr Sglty::Core::Major core_major = _core_major;
};

template <typename _core_traits, typename _enable>
struct IsValidCore;

}  // namespace Sglty::Traits

#include "Impl/Core.tpp"

// Singularity/Traits/Core.hpp
