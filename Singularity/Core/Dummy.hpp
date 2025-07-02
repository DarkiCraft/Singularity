#pragma once

#include <cstddef>

#include "Enums.hpp"

namespace Sglty::Core {

/**
 * @brief Dummy core implementation for placeholder or fallback behavior.
 *
 * `Dummy` is a trivial core used primarily for testing, trait validation,
 * or fallback scenarios in template contexts. It satisfies the full
 * interface required by `Matrix`, but does not represent any real storage.
 *
 * All type aliases and functions are valid, but the matrix is always treated
 * as 0×0 with a single dummy value.
 *
 * This type is not meant for actual numerical use — it only exists to
 * satisfy interface contracts.
 */
struct Dummy {
  /**
   * @brief Size traits for the Dummy core.
   *
   * Always represents a 0×0 matrix.
   */
  struct size_traits {
    static constexpr std::size_t rows = 0;
    static constexpr std::size_t cols = 0;
  };

  /**
   * @brief Type traits used by the Dummy core.
   *
   * Mimics a matrix of type `int`, with standard references and pointers.
   */
  struct type_traits {
    using size_type       = std::size_t;
    using value_type      = int;
    using difference_type = std::ptrdiff_t;
    using reference       = int&;
    using const_reference = const int&;
    using pointer         = int*;
    using const_pointer   = const int*;
  };

  /**
   * @brief Core traits describing storage type and layout.
   *
   * Pretends to be a row-major dense matrix (even though it stores nothing).
   */
  struct core_traits {
    static constexpr Sglty::Core::Type core_type   = Sglty::Core::Type::Dense;
    static constexpr Sglty::Core::Major core_major = Sglty::Core::Major::Row;
  };

  /**
   * @brief Alias to itself (used for trait compatibility).
   *
   * Required for satisfying the `core_base` alias in core concepts.
   */
  using core_base = Dummy;

  /**
   * @brief Rebinds to another Dummy regardless of size.
   *
   * Always returns `Dummy` — no actual size tracking is performed.
   */
  template <std::size_t, std::size_t>
  using core_rebind_size = Dummy;

  /**
   * @brief Accesses the single dummy element.
   *
   * Ignores the passed-in indices.
   *
   * @return Reference to internal dummy `int`.
   */
  int& At(std::size_t, std::size_t);

  /**
   * @brief Accesses the single dummy element (const version).
   *
   * Ignores the passed-in indices.
   *
   * @return Const reference to internal dummy `int`.
   */
  const int& At(std::size_t, std::size_t) const;

  /**
   * @brief Returns a pointer to the dummy data.
   *
   * Ignores actual indexing. Always returns the address of `val`.
   *
   * @return Pointer to internal dummy `int`.
   */
  int* Data();

  /**
   * @brief Returns a const pointer to the dummy data.
   *
   * Always returns the address of `val`.
   *
   * @return Const pointer to internal dummy `int`.
   */
  const int* Data() const;

 private:
  /// The only actual storage. Used as a placeholder for At() and Data().
  int val{};
};

}  // namespace Sglty::Core

#include "Impl/Dummy.tpp"

// Singularity/Core/Dummy.hpp
