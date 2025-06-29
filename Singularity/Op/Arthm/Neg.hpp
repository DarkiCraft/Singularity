#pragma once

#include <cstddef>

#include "../../Expr/Unary.hpp"

namespace Sglty::Expr {

struct Neg {
  template <typename _operand>
  constexpr static std::size_t rows = _operand::rows;

  template <typename _operand>
  constexpr static std::size_t cols = _operand::cols;

  template <typename _operand>
  using core_impl = typename _operand::core_impl;

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

namespace Sglty::Op::Arthm {

template <typename _operand>
constexpr auto Neg(const _operand& _o);

}  // namespace Sglty::Op::Arthm

namespace Sglty::Types {

template <typename _operand>
constexpr auto operator-(const _operand& _o);

}  // namespace Sglty::Types

#include "Impl/Neg.tpp"

// Singularity/Op/Arthm/Neg.hpp
