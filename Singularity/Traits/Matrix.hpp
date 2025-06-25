#pragma once

#include <type_traits>

namespace Sglty::Types {

template <typename _core>
class Matrix;  // forward declaration

}  // namespace Sglty::Types

namespace Sglty::Traits {

template <typename>
struct IsMatrix : std::false_type {};

template <typename _core>
struct IsMatrix<Types::Matrix<_core>> : std::true_type {};

template <typename _expr>
constexpr bool is_matrix_v = IsMatrix<_expr>::value;

}  // namespace Sglty::Traits

// Singularity/Traits/Matrix.hpp
