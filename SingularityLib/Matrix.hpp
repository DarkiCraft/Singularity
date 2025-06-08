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
  static_assert(has_size_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `size_traits`.");

  static_assert(has_type_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `type_traits`.");

  static_assert(has_core_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `core_traits`.");

  static_assert(_core_impl::size_traits::rows > 0 &&
                    _core_impl::size_traits::cols > 0,
                "Error: `size_traits::rows` and `size_traits:cols` must be positive." );

  static_assert(is_valid_core_traits_v<typename _core_impl::core_traits>,
                "Error: `_core_impl::core_traits` must be valid.");

  static_assert(has_member_functions_v<_core_impl>,
                "Error: `_core_impl` must provide member functions `At()` and "
                "`Data()` with correct signatures and return types.");

 public:
  using type_traits = typename _core_impl::type_traits;

  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  Matrix() {
    static_assert(std::is_default_constructible_v<_core_impl>,
                  "Error: attempting to default construct `_core_impl` which "
                  "is not default constructible.");
    std::fill(_m_data.Data(), _m_data.Data() + Rows() * Cols(), value_type());
  }

  constexpr Matrix(const Matrix& _other)     = default;
  constexpr Matrix(Matrix&& _other) noexcept = default;

  template <typename _core_other,
            bool _enable = !std::is_same_v<_core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const Matrix<_core_other>& _other) {
    static_assert(
        _core_impl::size_traits::rows == _core_other::size_traits::rows &&
            _core_impl::size_traits::cols == _core_other::size_traits::cols,
        "Error: dimension mismatch between `Matrix<_core_impl>` and "
        "`Matrix<_core_other>`.");

    for (size_t i = 0; i < Rows(); i++) {
      for (size_t j = 0; j < Cols(); j++) {
        _m_data.At(i, j) = _other._m_data.At(i, j);
      }
    }
  }

  constexpr Matrix& operator=(const Matrix& _other)     = default;
  constexpr Matrix& operator=(Matrix&& _other) noexcept = default;

  template <typename _core_other,
            bool _enable = !std::is_same_v<_core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix& operator=(const Matrix<_core_other>& _other) {
    static_assert(
        _core_impl::size_traits::rows == _core_other::size_traits::rows &&
            _core_impl::size_traits::cols == _core_other::size_traits::cols,
        "Error: dimension mismatch between `Matrix<_core_impl>` and "
        "`Matrix<_core_other>`.");

    Matrix<_core_other> temp(_other);

    for (size_t i = 0; i < Rows(); i++) {
      for (size_t j = 0; j < Cols(); j++) {
        _m_data.At(i, j) = temp._m_data.At(i, j);
      }
    }

    return *this;
  }

  template <typename... Args,
            bool _enable = (!std::is_constructible_v<Matrix, Args...> ||
                            sizeof...(Args) == 0 || sizeof...(Args) > 1),
            typename     = std::enable_if_t<_enable>>
  constexpr explicit Matrix(Args&&... args)
      : _m_data(std::forward<Args>(args)...) {
    static_assert(
        std::is_constructible_v<_core_impl, Args&&...>,
        "Error: `_core_impl` is not constructible with the passed arguments.");
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