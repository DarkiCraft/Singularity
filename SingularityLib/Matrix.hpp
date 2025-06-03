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

  static_assert(is_valid_core_traits_v<_core_impl::CoreType(),
                                       _core_impl::CoreMode(),
                                       _core_impl::CoreOrdr()>,
                "Invalid CoreTrait<> combination");

 public:
  template <
      typename _dummy_t = _core_impl,
      typename = std::enable_if_t<_dummy_t::CoreType() == CoreType::Static>>
  Matrix() {}

  template <
      typename _dummy_t = _core_impl,
      typename = std::enable_if_t<_dummy_t::CoreType() == CoreType::Dynamc>>
  Matrix(const size_t _rows, const size_t _cols) {}

 private:
  _core_impl _m_data;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_HPP

// SingularityLib/Matrix.hpp