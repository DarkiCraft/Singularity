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

template <typename _Tp>
using Mat2x2R = Types::Matrix<Core::Dense<_Tp, 2, 2, Core::Major::Row>>;

template <typename _Tp>
using Mat3x3R = Types::Matrix<Core::Dense<_Tp, 3, 3, Core::Major::Row>>;

template <typename _Tp>
using Mat4x4R = Types::Matrix<Core::Dense<_Tp, 4, 4, Core::Major::Row>>;

template <typename _Tp>
using Mat2x2C = Types::Matrix<Core::Dense<_Tp, 2, 2, Core::Major::Col>>;

template <typename _Tp>
using Mat3x3C = Types::Matrix<Core::Dense<_Tp, 3, 3, Core::Major::Col>>;

template <typename _Tp>
using Mat4x4C = Types::Matrix<Core::Dense<_Tp, 4, 4, Core::Major::Col>>;

}  // namespace Sglty

// Singularity/Convenience.hpp
