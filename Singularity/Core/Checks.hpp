#pragma once

namespace Sglty::Core {

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
struct HasRequiredTraits;

}  // namespace Sglty::Core

#include "Impl/Checks.tpp"

// Singularity/Core/Checks.hpp
