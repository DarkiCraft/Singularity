#pragma once

#include <cstddef>

#include "Tag.hpp"
#include "../Core/Dummy.hpp"

namespace Sglty::Expr {

/**
 * @brief Dummy expression node for placeholder use.
 *
 * `Expr::Dummy` is a no-op expression type used as a fallback, stub, or
 * default value during template instantiation or compile-time trait probing.
 *
 * It models a valid expression type with zero dimensions and delegates to
 * `Core::Dummy` for its `core_impl`.
 *
 * This is not intended for evaluation or real matrix expressions — it simply
 * exists to satisfy type requirements in metaprogramming.
 */
struct Dummy : Tag {
  /// Number of rows in the dummy expression (always zero).
  static constexpr std::size_t rows = 0;

  /// Number of columns in the dummy expression (always zero).
  static constexpr std::size_t cols = 0;

  /**
   * @brief The associated dummy core implementation.
   *
   * Always `Sglty::Core::Dummy`. Used to satisfy expression/core compatibility.
   */
  using core_impl = Core::Dummy;

  /**
   * @brief Trivial evaluation of the dummy expression.
   *
   * Always returns a dummy value — actual result is meaningless.
   * Exists to fulfill the expression interface contract.
   *
   * @param i Ignored row index.
   * @param j Ignored column index.
   * @return Dummy int value (reference to internal dummy state).
   */
  constexpr auto operator()(std::size_t i, std::size_t j) const;
};

}  // namespace Sglty::Expr

#include "Impl/Dummy.tpp"

// Singularity/Expr/Dummy.hpp