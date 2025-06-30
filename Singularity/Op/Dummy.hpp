#pragma once

#include "../Core/Dummy.hpp"

namespace Sglty::Op {

struct Dummy {
  template <typename, typename>
  static constexpr size_t rows = 0;

  template <typename, typename>
  static constexpr size_t cols = 0;

  template <typename, typename>
  using core_impl = Core::Dummy;

  template <typename, typename>
  constexpr static bool is_valid_core_impl = true;

  template <typename, typename>
  constexpr static bool is_valid_dimension = true;

  template <typename T, typename U>
  constexpr int operator()(const T&, const U&, std::size_t, std::size_t) const {
    return 0;
  }
};

}  // namespace Sglty::Op

// Singularity/Op/Dummy.hpp
