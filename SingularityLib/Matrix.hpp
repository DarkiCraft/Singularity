#ifndef SINGULARITYLIB_MATRIX_HPP
#define SINGULARITYLIB_MATRIX_HPP

#include <type_traits>

#include "Matrix/Core/Checks.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _core_impl>
class Matrix {
  static_assert(is_valid_core_implementation_v<_core_impl>,
                "Invalid Core Implementation");

  static_assert(is_valid_core_traits_v<typename _core_impl::core_traits>,
                "Invalid CoreTrait<> combination");

 public:
  Matrix() = default;

 private:
  _core_impl _m_data;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_HPP

// SingularityLib/Matrix.hpp