#pragma once

#include <cstddef>

#include "Tag.hpp"
#include "../Traits/Expr.hpp"
#include "../Traits/Op.hpp"
#include "../Traits/Core.hpp"

namespace Sglty::Expr {

template <typename _lhs, typename _rhs, typename _op>
struct Binary : Tag {
  using lhs_type = _lhs;
  using rhs_type = _rhs;

  static_assert(Traits::Expr::is_valid_v<lhs_type>,
                "Error: `_lhs` is not a valid expression type.");
  static_assert(Traits::Expr::is_valid_v<rhs_type>,
                "Error: `_rhs` is not a valid expression type.");

  using op_type = _op;

  static_assert(Traits::Op::is_valid_v<op_type>,
                "Error: `_op` is not a valid operation type.");

  using core_impl = typename op_type::core_impl<lhs_type, rhs_type>;

  static_assert(Traits::Core::is_valid_v<core_impl>,
                "Error: `_lhs` and `_rhs` produces invalid `core_impl` type.");

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
