#pragma once

#include "../Core/Dummy.hpp"

namespace Sglty::Op {

/**
 * @brief No-op placeholder operation for testing or default fallback.
 *
 * `Op::Dummy` is a compile-time operator that satisfies all trait contracts
 * but performs no meaningful computation. It always returns zero.
 *
 * Used for:
 * - Testing pipelines without needing a real operator.
 * - Placeholder in template defaults.
 */
struct Dummy {
  /**
   * @brief Always returns zero rows.
   */
  template <typename, typename>
  static constexpr std::size_t rows = 0;

  /**
   * @brief Always returns zero columns.
   */
  template <typename, typename>
  static constexpr std::size_t cols = 0;

  /**
   * @brief Always returns `Core::Dummy` as the core implementation.
   */
  template <typename, typename>
  using core_impl = Core::Dummy;

  /**
   * @brief Always valid as a core implementation.
   */
  template <typename, typename>
  constexpr static bool is_valid_core_impl = true;

  /**
   * @brief Always valid in terms of dimensions.
   */
  template <typename, typename>
  constexpr static bool is_valid_dimension = true;

  /**
   * @brief Returns zero regardless of inputs.
   *
   * @param i Ignored row index.
   * @param j Ignored column index.
   * @return Always 0.
   */
  template <typename T, typename U>
  constexpr int operator()(const T&, const U&, std::size_t, std::size_t) const {
    return 0;
  }
};

}  // namespace Sglty::Op

// Singularity/Op/Dummy.hpp
