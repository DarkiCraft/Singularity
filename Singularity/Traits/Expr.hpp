#pragma once

namespace Sglty::Traits::Expr {

template <typename _expr>
extern const bool has_tag_base_v;

template <typename _expr>
extern const bool has_interface_v;

template <typename _expr>
extern const bool is_valid_v;

}  // namespace Sglty::Traits::Expr

#include "Impl/Expr.tpp"

// Singularity/Traits/Expr.hpp
