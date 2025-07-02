#pragma once

namespace Sglty::Expr {

/**
 * @brief Evaluates a matrix expression at compile time.
 *
 * Accepts any valid expression type (typically a node from the `Expr` system)
 * and returns a `Matrix` constructed from it.
 *
 * This triggers compile-time evaluation of the expression tree and materializes
 * the result using the associated `core_impl` of the expression.
 *
 * The returned type is always a concrete `Matrix<core_impl>`, with all values
 * computed according to the expression logic.
 *
 * @tparam _expr The expression type. Must satisfy
 * `Sglty::Traits::Expr::is_valid_v`.
 * @param _e The expression to evaluate.
 * @return A concrete `Matrix` representing the evaluated expression.
 */
template <typename _expr>
constexpr auto Evaluate(const _expr& _e);

}  // namespace Sglty::Expr

#include "Impl/Evaluate.tpp"

// Singularity/Expr/Evaluate.hpp
