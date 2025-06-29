#pragma once

#include <cstddef>

#include "Tag.hpp"
#include "../Traits/Expr.hpp"
#include "../Core/Checks.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs, typename _op>
struct Binary : Tag {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  static_assert(Traits::is_expression_v<lhs_type>,
                "Error: lhs_type is not an expression type.");
  static_assert(Traits::is_expression_v<rhs_type>,
                "Error: rhs_type is not an expression type.");

  using op_type = _op;

  static_assert(Traits::is_valid_op_v<op_type>, "Error: op_type is invalid.");

  using core_impl = typename op_type::core_impl<lhs_type, rhs_type>;

  static_assert(Core::has_required_traits_v<core_impl>,
                "Error: lhs_type and rhs_type produce invalid core_impl.");

  constexpr static std::size_t rows =
      op_type::template rows<lhs_type, rhs_type>;
  constexpr static std::size_t cols =
      op_type::template cols<lhs_type, rhs_type>;

  constexpr Binary(const lhs_type& _l, const rhs_type& _r);

  constexpr auto operator()(std::size_t i, std::size_t j) const;

  const lhs_type _l;
  const rhs_type _r;
};

}  // namespace Sglty::Expr

#include "Impl/Binary.tpp"

// Singularity/Expr/Binary.hpp
