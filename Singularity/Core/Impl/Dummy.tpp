#pragma once

#include "../Dummy.hpp"

#include <cstddef>

namespace Sglty::Core {

inline int& Dummy::At(std::size_t, std::size_t) {
  return val;
}

inline const int& Dummy::At(std::size_t, std::size_t) const {
  return val;
}

inline int* Dummy::Data() {
  return &val;
}

inline const int* Dummy::Data() const {
  return &val;
}

}  // namespace Sglty::Core

// Singularity/Core/Impl/Dummy.tpp
