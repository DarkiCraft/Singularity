#pragma once

#include <cstddef>

#include "Tag.hpp"
#include "../Core/Dummy.hpp"

namespace Sglty::Expr {

struct Dummy : Tag {
  static constexpr std::size_t rows = 0;
  static constexpr std::size_t cols = 0;

  using core_impl = Core::Dummy;

  constexpr auto operator()(std::size_t, std::size_t) const;
};

}  // namespace Sglty::Expr

#include "Impl/Dummy.tpp"

// Singularity/Expr/Dummy.hpp