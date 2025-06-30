#pragma once

#include <cstddef>

#include "Core/Enums.hpp"

namespace Sglty::Core {

template <typename, std::size_t, std::size_t, Major>
class Dense;

}  // namespace Sglty::Core

namespace Sglty::Types {

template <typename>
class Matrix;

}  // namespace Sglty::Types

namespace Sglty {

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major = Core::Major::Row>
using DenseMat =
    Sglty::Types::Matrix<Sglty::Core::Dense<_Tp, _rows, _cols, _core_major>>;

}  // namespace Sglty

// Singularity/Convenience.hpp
