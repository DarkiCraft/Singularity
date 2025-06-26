#pragma once

namespace Sglty::Expr {

struct Tag;  // forward declaration to prevent circular includes

}  // namespace Sglty::Expr

namespace Sglty::Traits {

template <typename _expr, typename _enable>
struct IsExpression;

template <typename _op, typename _enable>
struct IsValidOp;

}  // namespace Sglty::Traits

#include "Impl/Expr.tpp"

// Singularity/Traits/Expr.hpp
