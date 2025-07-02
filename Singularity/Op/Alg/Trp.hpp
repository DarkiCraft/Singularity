#pragma once

#include <cstddef>

namespace Sglty::Expr {

/**
 * @brief Compile-time transpose operation.
 *
 * `Trp` defines the logic for the transpose of a matrix expression at compile
 * time. It inverts the shape of the operand and rebinds the core to reflect the
 * new size.
 *
 * This struct is used as the `op_type` for `Unary` expression nodes that
 * represent transposition. Evaluation is delegated to `operator()`.
 */
struct Trp {
  /**
   * @brief Number of rows in the resulting transposed matrix.
   *
   * Equals the number of columns in the operand.
   *
   * @tparam _operand The expression being transposed.
   */
  template <typename _operand>
  constexpr static std::size_t rows = _operand::cols;

  /**
   * @brief Number of columns in the resulting transposed matrix.
   *
   * Equals the number of rows in the operand.
   *
   * @tparam _operand The expression being transposed.
   */
  template <typename _operand>
  constexpr static std::size_t cols = _operand::rows;

  /**
   * @brief The core implementation type for the transposed result.
   *
   * This is derived by rebinding the operand's `core_impl` to its transposed
   * shape.
   *
   * @tparam _operand The operand expression.
   */
  template <typename _operand>
  using core_impl =
      typename _operand::core_impl::template core_rebind_size<rows<_operand>,
                                                              cols<_operand> >;

  /**
   * @brief Whether the operand is valid for core rebinding.
   *
   * Always `true` for transpose (by design — dimension-based only).
   */
  template <typename>
  constexpr static bool is_valid_core_impl = true;

  /**
   * @brief Whether the operand satisfies shape requirements.
   *
   * Always `true` for transpose (no shape restrictions).
   */
  template <typename>
  constexpr static bool is_valid_dimension = true;

  /**
   * @brief Evaluates the transpose at a given coordinate.
   *
   * Swaps the row and column indices to read `op(j, i)`.
   *
   * @tparam _operand The operand expression type.
   * @param op The operand to evaluate.
   * @param i The row index in the transposed view.
   * @param j The column index in the transposed view.
   * @return The element at (j, i) in the original operand.
   */
  template <typename _operand>
  constexpr auto operator()(const _operand& op,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Op::Alg {

/**
 * @brief Creates a transposed matrix expression.
 *
 * Wraps the given operand in a unary expression using the `Expr::Trp`
 * operation.
 *
 * @tparam _operand The operand expression type.
 * @param _o The operand to transpose.
 * @return A `Unary<_operand, Expr::Trp>` representing the transposed
 * expression.
 */
template <typename _operand>
constexpr auto Trp(const _operand& _o);

}  // namespace Sglty::Op::Alg

#include "Impl/Trp.tpp"

// Singularity/Op/Alg/Trp.hpp
