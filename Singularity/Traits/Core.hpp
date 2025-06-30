#pragma once

#include "../Core/Enums.hpp"

namespace Sglty::Traits::Core {

template <Sglty::Core::Type _core_type, Sglty::Core::Major _core_major>
struct Get {
  static constexpr Sglty::Core::Type core_type   = _core_type;
  static constexpr Sglty::Core::Major core_major = _core_major;

  static_assert(
      (core_type == Sglty::Core::Type::Dense &&
       (core_major == Sglty::Core::Major::Row ||
        core_major == Sglty::Core::Major::Col)) ||
          core_type == Sglty::Core::Type::Sparse,
      "Error: Invalid combination of `_core_type` and `_core_major` passed.");
};

}  // namespace Sglty::Traits::Core

namespace Sglty::Traits::Core::Impl {

template <typename _core_impl, typename _enable>
struct HasSizeTraits;

template <typename _core_impl, typename _enable>
struct HasTypeTraits;

template <typename _core_impl, typename _enable>
struct HasCoreTraits;

template <typename _core_impl, typename _enable>
struct HasRebindTraits;

template <typename _core_impl, typename _enable>
struct HasMemberFunctions;

template <typename _core_impl>
struct IsValid;

}  // namespace Sglty::Traits::Core::Impl

#include "Impl/Core.tpp"

// Singularity/Traits/Core.hpp
