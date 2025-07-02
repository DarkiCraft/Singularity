#pragma once

namespace Sglty::Expr {

/**
 * @brief Expression category type.
 *
 * Identifies whether an expression node represents a unary or binary operation.
 * This is mostly used for tagging and compile-time dispatch within the
 * expression system.
 */
enum class Type {
  /// Expression with a single operand (e.g., negation).
  Unary,

  /// Expression with two operands (e.g., addition, multiplication).
  Binary
};

}  // namespace Sglty::Expr

// Singularity/Expr/Enums.hpp
