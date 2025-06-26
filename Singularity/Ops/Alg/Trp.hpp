#pragma once

#include <cstddef>

namespace Sglty::Expr {

struct Trp {
  template <typename _operand>
  constexpr static std::size_t rows = _operand::cols;

  template <typename _operand>
  constexpr static std::size_t cols = _operand::rows;

  template <typename _operand>
  using core_type =
      typename _operand::core_type::template core_rebind<rows<_operand>,
                                                         cols<_operand>>;

  template <typename>
  constexpr static bool is_valid_core_type = true;

  template <typename>
  constexpr static bool is_valid_dimension = true;

  template <typename _operand>
  constexpr auto operator()(const _operand& op,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Ops::Alg {

template <typename _operand>
constexpr auto Trp(const _operand& _o);

}  // namespace Sglty::Ops::Alg

#include "Impl/Trp.tpp"

// Singularity/Ops/Alg/Trp.hpp
