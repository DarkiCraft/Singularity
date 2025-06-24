#pragma once

#include <cstddef>

#include "../Core/Checks.hpp"
#include "../Traits/Expr.hpp"
#include "Base.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs, typename _op>
struct Binary : Base<Binary<_lhs, _rhs, _op>> {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  static_assert(Traits::is_expression_v<lhs_type>,
                "Error: lhs_type is not an expression type.");
  static_assert(Traits::is_expression_v<rhs_type>,
                "Error: rhs_type is not an expression type.");

  using op_type = _op;

  static_assert(Traits::is_valid_op_v<op_type>, "Error: op_type is invalid.");

  using core_type = typename op_type::core_type<lhs_type, rhs_type>;

  static_assert(Core::is_valid_implementation_v<core_type>,
                "Error: lhs_type and rhs_type produce invalid core_type.");

  constexpr static std::size_t rows =
      op_type::template rows<lhs_type, rhs_type>;
  constexpr static std::size_t cols =
      op_type::template cols<lhs_type, rhs_type>;

  constexpr Binary(const lhs_type& _l, const rhs_type& _r) : _l(_l), _r(_r) {}

  constexpr auto operator()(std::size_t i, std::size_t j) const {
    return op_type{}(_l, _r, i, j);
  }

  const lhs_type _l;
  const rhs_type _r;
};

}  // namespace Sglty::Expr

// Singularity/Expr/Binary.hpp