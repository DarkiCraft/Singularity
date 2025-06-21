#pragma once

#include <cstddef>

namespace Sglty::Expr {

template <typename _derived>
struct Base {
  /**
   * @brief Returns a const reference to the derived class instance.
   *
   * Enables access to the derived class in CRTP-based inheritance.
   *
   * @return Const reference to the derived class.
   */
  constexpr const _derived& Derived() const {
    return static_cast<const _derived&>(*this);
  }

  constexpr static size_t rows = _derived::rows;
  constexpr static size_t cols = _derived::cols;

  /**
   * @brief Forwards element access to the derived class.
   *
   * Calls the derived class's `operator()(size_t, size_t)` to access the element at the specified row and column.
   *
   * @param i Row index.
   * @param j Column index.
   * @return The element at position (i, j) as provided by the derived class.
   */
  constexpr auto operator()(size_t i, size_t j) {
    return Derived()(i, j);
  }
};

}  // namespace Sglty::Expr

// Singularity/Expr/Base.hpp