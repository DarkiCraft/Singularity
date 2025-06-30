#pragma once

#include <cstddef>

#include "../Traits/Core.hpp"
#include "../Traits/Expr.hpp"
#include "../Traits/Op.hpp"
#include "Tag.hpp"

namespace Sglty::Expr {

template <typename _operand, typename _op>
struct Unary : Tag {
  using operand_type = _operand;

  static_assert(Traits::Expr::is_valid_v<operand_type>,
                "Error: `_operand` is not a valid expression type.");

  using op_type = _op;

  static_assert(Traits::Op::is_valid_v<op_type>,
                "Error: `_op` is not a valid operation type.");

  using core_impl = typename op_type::core_impl<operand_type>;

  static_assert(Traits::Core::is_valid_v<core_impl>,
                "Error: `_operand` produces invalid core_impl type.");

  constexpr static std::size_t rows = op_type::template rows<operand_type>;
  constexpr static std::size_t cols = op_type::template cols<operand_type>;

  constexpr Unary(const operand_type& _o);

  constexpr auto operator()(std::size_t i, std::size_t j) const;

  const operand_type _o;
};

}  // namespace Sglty::Expr

#include "Impl/Unary.tpp"

// Singularity/Expr/Unary.hpp
