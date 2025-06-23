#pragma once

#include "Base.hpp"

namespace Sglty::Expr {

template <typename _operand, typename _op>
struct Unary : Base<Unary<_operand, _op>> {
  using operand_type = _operand;
  using op_type      = _op;
  using core_type    = typename op_type::core_type<operand_type>;

  constexpr Unary(const operand_type& _o) : _o(_o) {}

  constexpr auto operator()(size_t i, size_t j) const {
    return op_type{}(_o, i, j);
  }

  constexpr static size_t rows = op_type::template rows<operand_type>;
  constexpr static size_t cols = op_type::template cols<operand_type>;

  const operand_type _o;
};

}  // namespace Sglty::Expr

// Singularity/Expr/Unary.hpp