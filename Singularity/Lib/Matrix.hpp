#ifndef SINGULARITY_MATRIX_HPP
#define SINGULARITY_MATRIX_HPP

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>

#include "Core/Checks.hpp"
#include "Expr/Base.hpp"
#include "Traits/Expr.hpp"

namespace Sglty {

template <typename _core_impl>
class Matrix : public Expr::Base<Matrix<_core_impl>> {
  static_assert(Core::has_size_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `size_traits`.");

  static_assert(Core::has_type_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `type_traits`.");

  static_assert(Core::has_core_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `core_traits`.");

  static_assert(
      _core_impl::size_traits::rows > 0 && _core_impl::size_traits::cols > 0,
      "Error: `size_traits::rows` and `size_traits:cols` must be positive.");

  static_assert(Traits::is_valid_core_v<typename _core_impl::core_traits>,
                "Error: `_core_impl::core_traits` must be valid.");

  static_assert(Core::has_member_functions_v<_core_impl>,
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

  constexpr static auto core_mode  = core_traits::core_mode;
  constexpr static auto core_order = core_traits::core_order;

  using core_type = _core_impl;

  constexpr Matrix() : _m_data{} {
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

    TraverseIndices([&](size_t i, size_t j) { (*this)(i, j) = _other(i, j); });
  }

  template <typename _expr,
            bool _enable = is_expression_v<std::decay_t<_expr>>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const _expr& _e) {
    TraverseIndices([&](size_t i, size_t j) { (*this)(i, j) = _e(i, j); });
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

    TraverseIndices([&](size_t i, size_t j) { (*this)(i, j) = temp(i, j); });

    return *this;
  }

  template <typename _expr,
            bool _enable = is_expression_v<std::decay_t<_expr>>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix& operator=(const _expr& _e) {
    static_assert(rows == _expr::rows && cols == _expr::cols,
                  "Error: dimension mismatch between `*this` and `_expr`.");

    TraverseIndices([&](size_t i, size_t j) { (*this)(i, j) = _e(i, j); });

    return *this;
  }

  template <typename... Args,
            bool _enable = sizeof...(Args) != 0 &&
                           !(sizeof...(Args) == 1 &&
                             ((std::is_same_v<std::decay_t<Args>, Matrix> ||
                               Sglty::is_expression_v<std::decay_t<Args>>) ||
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

  constexpr Core::Mode Mode() const {
    return core_mode;
  }
  constexpr Core::Order Order() const {
    return core_order;
  }

  constexpr reference operator()(const size_type _row, const size_type _col) {
    return const_cast<reference>(std::as_const(*this).operator()(_row, _col));
  }
  constexpr const_reference operator()(const size_type _row,
                                       const size_type _col) const {
    return _m_data.At(_row, _col);
  }

  template <typename Func>
  constexpr void TraverseIndices(Func&& fn) {
    std::as_const(*this).TraverseIndices(
        [&](size_type i, size_type j) { fn(i, j); });
  }

  template <typename Func>
  constexpr void TraverseIndices(Func&& fn) const {
    if constexpr (Order() == Core::Order::RowMajor) {
      for (size_t i = 0; i < Rows(); i++) {
        for (size_t j = 0; j < Cols(); j++) {
          fn(i, j);
        }
      }
    } else {
      for (size_t j = 0; j < Cols(); j++) {
        for (size_t i = 0; i < Rows(); i++) {
          fn(i, j);
        }
      }
    }
  }

  template <typename Func>
  constexpr void TraverseValues(Func&& fn) {
    std::as_const(*this).TraverseValues([&](value_type val) { fn(val); });
  }

  template <typename Func>
  constexpr void TraverseValues(Func&& fn) const {
    if constexpr (Order() == Core::Order::RowMajor) {
      for (size_t i = 0; i < Rows(); i++) {
        for (size_t j = 0; j < Cols(); j++) {
          fn((*this)(i, j));
        }
      }
    } else {
      for (size_t j = 0; j < Cols(); j++) {
        for (size_t i = 0; i < Rows(); i++) {
          fn((*this)(i, j));
        }
      }
    }
  }

  template <typename _expr>
  constexpr Matrix& operator+=(const _expr& _e) {
    static_assert(is_expression_v<_expr>, "Error: non-expression passed");
    static_assert(Matrix::rows == _expr::rows && Matrix::cols == _expr::cols,
                  "Error: dimension mismatch.");

    TraverseIndices([&](size_t i, size_t j) { (*this)(i, j) += _e(i, j); });
    return (*this);
  }

  template <typename _scalar>
  constexpr Matrix& operator*=(const _scalar _other) {
    static_assert(std::is_arithmetic_v<_scalar>,
                  "Error: non-integral value passed.");

    TraverseIndices([&](size_t i, size_t j) { (*this)(i, j) *= _other; });
    return (*this);
  }

  template <typename _expr>
  constexpr Matrix& operator-=(const _expr& _e) {
    static_assert(is_expression_v<_expr>, "Error: non-expression passed");
    static_assert(Matrix::rows == _expr::rows && Matrix::cols == _expr::cols,
                  "Error: dimension mismatch.");

    return (*this) += _e * -1;
  }

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

}  // namespace Sglty

#endif  // SINGULARITY_MATRIX_HPP

// Singularity/Matrix.hpp