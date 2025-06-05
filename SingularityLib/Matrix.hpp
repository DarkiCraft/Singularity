#ifndef SINGULARITYLIB_MATRIX_HPP
#define SINGULARITYLIB_MATRIX_HPP

#include <type_traits>

#include "Matrix/Core/Checks.hpp"

using std::size_t;

namespace Sglty {

template <typename _core_impl>
class Matrix {
  // static_assert(is_valid_core_implementation_v<_core_impl>,
  //               "Invalid Core Implementation");

  static_assert(has_type_traits_v<_core_impl>, "Missing nested type_traits");
  static_assert(has_core_traits_v<_core_impl>, "Missing nested core_traits");
  static_assert(has_static_functions_v<_core_impl>,
                "Missing static Rows() or Cols() with integral return type");
  static_assert(has_member_functions_v<_core_impl>,
                "Missing At() or Data() or wrong signature or return type");
  static_assert(is_valid_core_traits_v<typename _core_impl::core_traits>,
                "Invalid core_traits combination");

 public:
  Matrix() = default;

  // this for testing, will be implemented correctly later
  template <typename _core>
  friend constexpr Matrix<_core> operator+(const Matrix<_core>& l,
                                           const Matrix<_core>& r) {
    Matrix<_core> result;
    for (size_t i = 0; i < result._m_data.Rows(); i++) {
      for (size_t j = 0; j < result._m_data.Cols(); j++) {
        result._m_data.At(i, j) = l._m_data.At(i, j) + r._m_data.At(i, j);
      }
    }

    return result;
  }

 private:
  _core_impl _m_data;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_HPP

// SingularityLib/Matrix.hpp