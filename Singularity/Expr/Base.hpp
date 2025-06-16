#ifndef SINGULARITY_EXPR_BASE_HPP
#define SINGULARITY_EXPR_BASE_HPP

namespace Sglty {

template <typename _derived>
struct ExprBase {
  constexpr const _derived& Derived() const {
    return static_cast<const _derived&>(*this);
  }

  constexpr static size_t rows = _derived::rows;
  constexpr static size_t cols = _derived::cols;

  constexpr auto operator()(size_t i, size_t j) {
    return Derived()(i, j);
  }
};

// template <typename Expr>
// struct get_leftmost_core {
//   using type = typename Expr::core_type;  // matrix exposes core_type
// };

}  // namespace Sglty

#endif  // SINGULARITY_EXPR_BASE_HPP

// Singularity/Expr/Base.hpp