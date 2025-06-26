#pragma once

#include "../Matrix.hpp"

#include <type_traits>

namespace Sglty::Types {

template <typename _core_impl>
class Matrix;  // forward declaration

}  // namespace Sglty::Types

namespace Sglty::Traits {

template <typename _core_impl>
struct IsMatrix : std::false_type {};

template <typename _core_impl>
struct IsMatrix<Types::Matrix<_core_impl>> : std::true_type {};

template <typename _expr>
constexpr bool is_matrix_v = IsMatrix<_expr>::value;

}  // namespace Sglty::Traits

// Singularity/Traits/Impl/Matrix.tpp
