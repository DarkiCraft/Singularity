#pragma once

#include <type_traits>

// #include "../Matrix.hpp" // this breaks, using forward declaration for now

namespace Sglty {

template <typename _core>
class Matrix;  // forward declaration

template <typename>
struct IsMatrix : std::false_type {};

template <typename _core>
struct IsMatrix<Sglty::Matrix<_core>> : std::true_type {};

template <typename _expr>
constexpr bool is_matrix_v = IsMatrix<_expr>::value;

}  // namespace Sglty

// Singularity/Traits/Matrix.hpp