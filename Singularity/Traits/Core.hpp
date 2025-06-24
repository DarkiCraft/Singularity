#pragma once

#include <cstddef>
#include <type_traits>

#include "../Core/Enums.hpp"

namespace Sglty::Traits {

template <Sglty::Core::Mode _core_mode, Sglty::Core::Order _core_order>
struct Core {
  static constexpr Sglty::Core::Mode core_mode   = _core_mode;
  static constexpr Sglty::Core::Order core_order = _core_order;
};

template <typename, typename = void>
struct IsValidCore : std::false_type {};

template <typename _core_traits>
struct IsValidCore<_core_traits,
                   std::void_t<decltype(_core_traits::core_mode),
                               decltype(_core_traits::core_order)>>
    : std::bool_constant<
          (_core_traits::core_mode == Sglty::Core::Mode::Dense &&
           (_core_traits::core_order == Sglty::Core::Order::RowMajor ||
            _core_traits::core_order == Sglty::Core::Order::ColMajor)) ||
          _core_traits::core_mode == Sglty::Core::Mode::Sparse> {};

template <typename core_traits>
constexpr bool is_valid_core_v = IsValidCore<core_traits>::value;

struct DummyCore {
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

  using core_base = DummyCore;

  template <std::size_t, std::size_t>
  using core_rebind = DummyCore;

  int& At(std::size_t, std::size_t) {
    static int val = 0;
    return val;
  }

  const int& At(std::size_t, std::size_t) const {
    static const int val = 0;
    return val;
  }

  int* Data() {
    static int val = 0;
    return &val;
  }

  const int* Data() const {
    static const int val = 0;
    return &val;
  }
};

}  // namespace Sglty::Traits

// Singularity/Traits/Core.hpp