#pragma once

#include "../Core/Enums.hpp"

namespace Sglty::Traits {

template <Sglty::Core::Mode _core_mode, Sglty::Core::Major _core_major>
struct Core {
  static constexpr Sglty::Core::Mode core_mode   = _core_mode;
  static constexpr Sglty::Core::Major core_major = _core_major;
};

template <typename _core_traits, typename _enable>
struct IsValidCore;

}  // namespace Sglty::Traits

#include "Impl/Core.tpp"

// Singularity/Traits/Core.hpp
