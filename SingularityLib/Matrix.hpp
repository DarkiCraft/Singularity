#ifndef SINGULARITYLIB_MATRIX_HPP
#define SINGULARITYLIB_MATRIX_HPP

#include <iostream>
#include <type_traits>
#include <utility>

#include "Matrix/Core/Checks.hpp"

using std::size_t;

namespace Sglty {

template <typename _core_impl>
class Matrix {
  static_assert(has_size_traits_v<_core_impl>, "Missing nested size_traits");
  static_assert(has_type_traits_v<_core_impl>, "Missing nested type_traits");
  static_assert(has_core_traits_v<_core_impl>, "Missing nested core_traits");
  static_assert(is_valid_core_traits_v<typename _core_impl::core_traits>,
                "Invalid core_traits combination");
  static_assert(has_member_functions_v<_core_impl>,
                "Missing At() or Data(), or wrong signature or return type");

 public:
  using type_traits = typename _core_impl::type_traits;

  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  Matrix() {
    std::fill(_m_data.Data(), _m_data.Data() + Rows() * Cols(), value_type());
  }

  constexpr size_t Rows() const {
    return _core_impl::size_traits::rows;
  }
  constexpr size_t Cols() const {
    return _core_impl::size_traits::cols;
  }

  constexpr reference operator()(const size_t _row, const size_t _col) {
    return const_cast<reference>(std::as_const(*this).operator()(_row, _col));
  }

  constexpr const_reference operator()(const size_t _row,
                                       const size_t _col) const {
    return _m_data.At(_row, _col);
  }

  // template <typename _core>
  // friend constexpr Matrix<_core> operator+(const Matrix<_core>& l,
  //                                          const Matrix<_core>& r) {
  //   Matrix<_core> result;
  //   for (size_t i = 0; i < result.Rows(); i++) {
  //     for (size_t j = 0; j < result.Cols(); j++) {
  //       result(i, j) = l(i, j) + r(i, j);
  //     }
  //   }

  //   return result;
  // }

  // template <typename _core,
  //           typename _integral,
  //           bool _enable = std::is_integral_v<_integral>,
  //           typename     = std::enable_if_t<_enable>>
  // friend constexpr Matrix<_core> operator*(const Matrix<_core>& l,
  //                                          const _integral r) {
  //   Matrix<_core> result;
  //   for (size_t i = 0; i < result.Rows(); i++) {
  //     for (size_t j = 0; j < result.Cols(); j++) {
  //       result(i, j) = l(i, j) * r;
  //     }
  //   }

  //   return result;
  // }

  // template <typename _core,
  //           typename _integral,
  //           bool _enable = std::is_integral_v<_integral>,
  //           typename     = std::enable_if_t<_enable>>
  // friend constexpr Matrix<_core> operator*(const _integral l,
  //                                          const Matrix<_core>& r) {
  //   return r * l;
  // }

  // temporary for tests
  void Print() const {
    for (size_t i = 0; i < Rows(); i++) {
      for (size_t j = 0; j < Cols(); j++) {
        std::cout << (*this)(i, j) << ' ';
      }
      std::cout << '\n';
    }
  }

 private:
  _core_impl _m_data;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_HPP

// SingularityLib/Matrix.hpp