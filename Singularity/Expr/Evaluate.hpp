#pragma once

namespace Sglty::Expr {

template <typename _expr>
constexpr auto Evaluate(const _expr& _e);

}  // namespace Sglty::Expr

#include "Impl/Evaluate.tpp"

// Singularity/Expr/Evaluate.hpp
