#ifndef SINGULARITY_EXPR_BASE_HPP
#define SINGULARITY_EXPR_BASE_HPP

namespace Sglty {

namespace Expr {
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

}  // namespace Expr

}  // namespace Sglty

#endif  // SINGULARITY_EXPR_BASE_HPP

// Singularity/Expr/Base.hpp