#pragma once

#include <cstddef>

namespace Sglty::Expr {

template <typename _derived>
struct Base {
  constexpr const _derived& Derived() const {
    return static_cast<const _derived&>(*this);
  }

  constexpr static std::size_t rows = _derived::rows;
  constexpr static std::size_t cols = _derived::cols;

  constexpr auto operator()(std::size_t i, std::size_t j) const {
    return Derived()(i, j);
  }
};

}  // namespace Sglty::Expr

// Singularity/Expr/Base.hpp