#pragma once

#include <cstddef>

namespace Sglty::Expr {

struct Trp {
  template <typename _operand>
  constexpr static std::size_t rows = _operand::cols;

  template <typename _operand>
  constexpr static std::size_t cols = _operand::rows;

  template <typename _operand>
  using core_impl =
      typename _operand::core_impl::template core_rebind_size<rows<_operand>,
                                                              cols<_operand>>;

  template <typename>
  constexpr static bool is_valid_core_impl = true;

  template <typename>
  constexpr static bool is_valid_dimension = true;

  template <typename _operand>
  constexpr auto operator()(const _operand& op,
                            std::size_t i,
                            std::size_t j) const;
};

}  // namespace Sglty::Expr

namespace Sglty::Op::Alg {

template <typename _operand>
constexpr auto Trp(const _operand& _o);

}  // namespace Sglty::Op::Alg

#include "Impl/Trp.tpp"

// Singularity/Op/Alg/Trp.hpp
