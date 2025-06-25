#pragma once

#include <cstddef>

#include "Enums.hpp"

namespace Sglty::Core {

struct Dummy {
  struct size_traits {
    static constexpr std::size_t rows = 0;
    static constexpr std::size_t cols = 0;
  };

  struct type_traits {
    using size_type       = std::size_t;
    using value_type      = int;
    using difference_type = std::ptrdiff_t;
    using reference       = int&;
    using const_reference = const int&;
    using pointer         = int*;
    using const_pointer   = const int*;
  };

  struct core_traits {
    static constexpr Sglty::Core::Mode core_mode = Sglty::Core::Mode::Dense;
    static constexpr Sglty::Core::Order core_order =
        Sglty::Core::Order::RowMajor;
  };

  using core_base = Dummy;

  template <std::size_t, std::size_t>
  using core_rebind = Dummy;

  int& At(std::size_t, std::size_t) {
    return val;
  }

  const int& At(std::size_t, std::size_t) const {
    return val;
  }

  int* Data() {
    return &val;
  }

  const int* Data() const {
    return &val;
  }

 private:
  int val{};
};

}  // namespace Sglty::Core

// Singularity/Core/Dummy.hpp
