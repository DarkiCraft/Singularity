#pragma once

#include <cstddef>

#include "../Core/Checks.hpp"
#include "../Traits/Expr.hpp"
#include "Tag.hpp"

namespace Sglty::Expr {

template <typename _operand, typename _op>
struct Unary : Tag {
  using operand_type = _operand;

  static_assert(Traits::is_expression_v<operand_type>,
                "Error: operand_type is not an expression type.");

  using op_type = _op;

  static_assert(Traits::is_valid_op_v<op_type>, "Error: op_type is invalid.");

  using core_type = typename op_type::core_type<operand_type>;

  static_assert(Core::has_required_traits_v<core_type>,
                "Error: operand_type produces invalid core_type.");

  constexpr static std::size_t rows = op_type::template rows<operand_type>;
  constexpr static std::size_t cols = op_type::template cols<operand_type>;

  constexpr Unary(const operand_type& _o) : _o(_o) {}

  constexpr auto operator()(std::size_t i, std::size_t j) const {
    return op_type{}(_o, i, j);
  }

  const operand_type _o;
};

}  // namespace Sglty::Expr

// Singularity/Expr/Unary.hpp
