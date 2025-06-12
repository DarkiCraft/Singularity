#ifndef SINGULARITYLIB_MATRIX_HPP
#define SINGULARITYLIB_MATRIX_HPP

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>

#include "Expr/Base.hpp"
#include "Matrix/Core/Checks.hpp"

namespace Sglty {

template <typename _core_impl>
class Matrix : public ExprBase<Matrix<_core_impl>> {
  static_assert(has_size_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `size_traits`.");

  static_assert(has_type_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `type_traits`.");

  static_assert(has_core_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `core_traits`.");

  static_assert(
      _core_impl::size_traits::rows > 0 && _core_impl::size_traits::cols > 0,
      "Error: `size_traits::rows` and `size_traits:cols` must be positive.");

  static_assert(is_valid_core_traits_v<typename _core_impl::core_traits>,
                "Error: `_core_impl::core_traits` must be valid.");

  static_assert(has_member_functions_v<_core_impl>,
                "Error: `_core_impl` must provide member functions `At()` and "
                "`Data()` with correct signatures and return types.");

  template <typename>
  friend class Matrix;

 public:
  using type_traits = typename _core_impl::type_traits;

  using size_type       = typename type_traits::size_type;
  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  using size_traits = typename _core_impl::size_traits;

  constexpr static auto rows = size_traits::rows;
  constexpr static auto cols = size_traits::cols;

  using core_traits = typename _core_impl::core_traits;

  constexpr static auto core_mode = core_traits::core_mode;
  constexpr static auto core_ordr = core_traits::core_ordr;

  Matrix() : _m_data{} {
    static_assert(std::is_default_constructible_v<_core_impl>,
                  "Error: attempting to default construct `_core_impl` which "
                  "is not default constructible.");
  }

  constexpr Matrix(const Matrix& _other)     = default;
  constexpr Matrix(Matrix&& _other) noexcept = default;

  template <typename _core_other,
            bool _enable = !std::is_same_v<_core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const Matrix<_core_other>& _other) {
    static_assert(Matrix<_core_impl>::rows == Matrix<_core_other>::rows &&
                      Matrix<_core_impl>::cols == Matrix<_core_other>::cols,
                  "Error: dimension mismatch between `Matrix<_core_impl>` and "
                  "`Matrix<_core_other>`.");

    for (size_type i = 0; i < Rows(); i++) {
      for (size_type j = 0; j < Cols(); j++) {
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
    static_assert(Matrix<_core_impl>::rows == Matrix<_core_other>::rows &&
                      Matrix<_core_impl>::cols == Matrix<_core_other>::cols,
                  "Error: dimension mismatch between `Matrix<_core_impl>` and "
                  "`Matrix<_core_other>`.");

    Matrix<_core_other> temp(_other);

    for (size_type i = 0; i < Rows(); i++) {
      for (size_type j = 0; j < Cols(); j++) {
        _m_data.At(i, j) = temp._m_data.At(i, j);
      }
    }

    return *this;
  }

  template <typename... Args,
            bool _enable = sizeof...(Args) != 0 &&
                           !(sizeof...(Args) == 1 &&
                             (std::is_same_v<std::decay_t<Args>, Matrix> ||
                              ...)),
            typename = std::enable_if_t<_enable>>
  constexpr explicit Matrix(Args&&... args)
      : _m_data(std::forward<Args>(args)...) {
    static_assert(
        std::is_constructible_v<_core_impl, Args&&...>,
        "Error: `_core_impl` is not constructible with the passed arguments.");
  }

  constexpr size_type Rows() const {
    return rows;
  }
  constexpr size_type Cols() const {
    return cols;
  }

  constexpr CoreMode CoreMode() const {
    return core_mode;
  }
  constexpr CoreOrdr CoreOrdr() const {
    return core_ordr;
  }

  constexpr reference operator()(const size_type _row, const size_type _col) {
    return const_cast<reference>(std::as_const(*this).operator()(_row, _col));
  }
  constexpr const_reference operator()(const size_type _row,
                                       const size_type _col) const {
    return _m_data.At(_row, _col);
  }

  template <typename _core_other>
  constexpr Matrix<_core_impl> operator+=(const Matrix<_core_other>& _other) {
    static_assert(
        Matrix<_core_impl>::rows == Matrix<_core_other>::rows &&
            Matrix<_core_impl>::cols == Matrix<_core_other>::cols,
        "Error: dimension mismatch between `*this` and `Matrix<_core_other>`.");

    for (size_type i = 0; i < Rows(); i++) {
      for (size_type j = 0; j < Cols(); j++) {
        (*this)(i, j) += _other(i, j);
      }
    }
    return (*this);
  }

  template <typename _integral>
  constexpr Matrix<_core_impl> operator*=(const _integral _other) {
    static_assert(std::is_integral_v<_integral>,
                  "Error: non-integral value passed for `_integral`.");

    for (size_type i = 0; i < Rows(); i++) {
      for (size_type j = 0; j < Cols(); j++) {
        (*this)(i, j) *= _other;
      }
    }
    return (*this);
  }

  template <typename _core_other>
  constexpr Matrix<_core_impl> operator-=(const Matrix<_core_other>& _other) {
    static_assert(
        Matrix<_core_impl>::rows == Matrix<_core_other>::rows &&
            Matrix<_core_impl>::cols == Matrix<_core_other>::cols,
        "Error: dimension mismatch between `*this` and `Matrix<_core_other>`.");

    return (*this) += _other * -1;
  }

  template <typename _core_l, typename _core_r, typename _core_def>
  friend constexpr Matrix<_core_def> operator+(const Matrix<_core_l>& l,
                                               const Matrix<_core_r>& r);

  template <typename _core_l, typename _core_r, typename _core_def>
  friend constexpr Matrix<_core_def> operator-(const Matrix<_core_l>& l,
                                               const Matrix<_core_r>& r);

  template <typename _core, typename _integral>
  friend constexpr Matrix<_core> operator*(const Matrix<_core>& l,
                                           const _integral r);

  template <typename _core, typename _integral>
  friend constexpr Matrix<_core> operator*(const _integral l,
                                           const Matrix<_core>& r);

  template <typename _core_l, typename _core_r, typename _core_def>
  friend constexpr Matrix<
      typename _core_def::core_rebind<_core_l::size_traits::rows,
                                      _core_l::size_traits::cols>>
  operator*(const Matrix<_core_l>& l, const Matrix<_core_r>& r);

  // temporary for tests
  void Print() const {
    for (size_type i = 0; i < Rows(); i++) {
      for (size_type j = 0; j < Cols(); j++) {
        std::cout << (*this)(i, j) << ' ';
      }
      std::cout << '\n';
    }
  }

 private:
  _core_impl _m_data;
};

template <typename _core_l, typename _core_r, typename _core_def = _core_l>
constexpr Matrix<_core_def> operator+(const Matrix<_core_l>& l,
                                      const Matrix<_core_r>& r) {
  Matrix<_core_def> result(l);
  return result += r;
}

template <typename _core_l, typename _core_r, typename _core_def = _core_l>
constexpr Matrix<_core_def> operator-(const Matrix<_core_l>& l,
                                      const Matrix<_core_r>& r) {
  Matrix<_core_def> result(l);
  return result -= r;
}

template <typename _core, typename _integral>
constexpr Matrix<_core> operator*(const Matrix<_core>& l, const _integral r) {
  Matrix<_core> result(l);
  return result *= r;
}

template <typename _core, typename _integral>
constexpr Matrix<_core> operator*(const _integral l, const Matrix<_core>& r) {
  return r * l;
}

template <typename _core_l, typename _core_r, typename _core_def = _core_l>
constexpr Matrix<typename _core_def::core_rebind<_core_l::size_traits::rows,
                                                 _core_r::size_traits::cols>>
operator*(const Matrix<_core_l>& l, const Matrix<_core_r>& r) {
  static_assert(_core_l::size_traits::cols == _core_r::size_traits::rows,
                "Error: dimension mismatch between `Matrix<_core_l>` and "
                "`Matrix<_core_r>`.");

  using size_type = typename Matrix<_core_def>::size_type;

  constexpr size_type R = _core_l::size_traits::rows;
  constexpr size_type C = _core_r::size_traits::cols;
  constexpr size_type K = _core_l::size_traits::cols;

  using _result_core = typename _core_def::core_rebind<R, C>;
  Matrix<_result_core> result{};  // Zero-initialized to avoid garbage

  for (size_type i = 0; i < R; i++) {
    for (size_type k = 0; k < K; k++) {
      auto sum = l(i, k);
      for (size_type j = 0; j < C; j++) {
        result(i, j) += sum * r(k, j);
      }
    }
  }

  return result;
}

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_HPP

// SingularityLib/Matrix.hpp