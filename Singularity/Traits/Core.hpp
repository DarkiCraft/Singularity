#pragma once

#include "../Core/Enums.hpp"

namespace Sglty::Traits::Core {

template <Sglty::Core::Type _core_type, Sglty::Core::Major _core_major>
struct Get;

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
