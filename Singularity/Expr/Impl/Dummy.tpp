#pragma once

#include "../Dummy.hpp"

#include <cstddef>

#include "../../Op/Dummy.hpp"

namespace Sglty::Expr {

constexpr auto Dummy::operator()(std::size_t i, std::size_t j) const {
  return Op::Dummy{}(Dummy{}, Dummy{}, i, j);
}

}  // namespace Sglty::Expr

// Singularity/Expr/Impl/Dummy.tpp
