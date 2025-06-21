#pragma once

#include <cstddef>

namespace Sglty::Expr {

template <typename _derived>
struct Base {
  constexpr const _derived& Derived() const {
    return static_cast<const _derived&>(*this);
  }

  constexpr static size_t rows = _derived::rows;
  constexpr static size_t cols = _derived::cols;

  constexpr auto operator()(size_t i, size_t j) {
    return Derived()(i, j);
  }
};

}  // namespace Sglty::Expr

// Singularity/Expr/Base.hpp