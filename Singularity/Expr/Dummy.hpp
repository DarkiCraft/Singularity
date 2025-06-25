#pragma once

#include "../Core/Dummy.hpp"
#include "../Ops/Dummy.hpp"
#include "Tag.hpp"

namespace Sglty::Expr {

struct Dummy : Tag {
  static constexpr size_t rows = 0;
  static constexpr size_t cols = 0;

  using core_type = Core::Dummy;

  constexpr auto operator()(size_t, size_t) const {
    return Ops::Dummy{}(Dummy(), Dummy(), 0, 0);
  }
};

}  // namespace Sglty::Expr

// Singularity/Expr/Dummy.hpp