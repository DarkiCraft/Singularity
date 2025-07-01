#pragma once

#include "../Core/Enums.hpp"

namespace Sglty::Traits::Core {

template <Sglty::Core::Type _core_type, Sglty::Core::Major _core_major>
struct Get;

}  // namespace Sglty::Traits::Core

namespace Sglty::Traits::Core {

template <typename _core_impl>
extern const bool has_size_traits_v;

template <typename _core_impl>
extern const bool has_type_traits_v;

template <typename _core_impl>
extern const bool has_core_traits_v;

template <typename _core_impl>
extern const bool has_rebind_traits_v;

template <typename _core_impl>
extern const bool has_member_functions_v;

template <typename _core_impl>
extern const bool is_valid_v;

}  // namespace Sglty::Traits::Core

#include "Impl/Core.tpp"

// Singularity/Traits/Core.hpp
