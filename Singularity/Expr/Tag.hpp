#pragma once

#include <cstddef>

namespace Sglty::Expr {

/**
 * @brief Marker base class for all expression types.
 *
 * Inherit from `Expr::Tag` to indicate that a type is part of the expression
 * system. This is used for trait checks like `is_valid_v` to distinguish
 * expression nodes from other types during compile-time introspection.
 *
 * `Matrix` also inherits from `Tag`, allowing it to participate in expression
 * trees.
 */
struct Tag {};

}  // namespace Sglty::Expr

// Singularity/Expr/Tag.hpp
