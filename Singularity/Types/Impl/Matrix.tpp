#pragma once

#include "../Matrix.hpp"

#include <iostream>
#include <type_traits>
#include <utility>

#include "../../Traits/Expr.hpp"
#include "../../Ops/Arthm/Neg.hpp"

namespace Sglty::Types {

template <typename _core_impl>
Matrix<_core_impl>::Matrix() {
  static_assert(std::is_default_constructible_v<_core_impl>,
                "Error: attempting to default construct `_core_impl` which "
                "is not default constructible.");
}

template <typename _core_impl>
template <typename _core_other, bool _enable, typename>
constexpr Matrix<_core_impl>::Matrix(const Matrix<_core_other>& _other) {
  static_assert(Matrix<_core_impl>::rows == Matrix<_core_other>::rows &&
                    Matrix<_core_impl>::cols == Matrix<_core_other>::cols,
                "Error: dimension mismatch between `Matrix<_core_impl>` and "
                "`Matrix<_core_other>`.");

  TraverseIndices(
      [&](std::size_t i, std::size_t j) { (*this)(i, j) = _other(i, j); });
}

template <typename _core_impl>
template <typename _expr, bool _enable, typename>
constexpr Matrix<_core_impl>::Matrix(const _expr& _e) : _m_data() {
  static_assert(
      std::is_same_v<typename Matrix::core_type, typename _expr::core_type>,
      "Error: `core_type` mismatch.");

  TraverseIndices(
      [&](std::size_t i, std::size_t j) { (*this)(i, j) = _e(i, j); });
}

template <typename _core_impl>
template <typename _core_other, bool _enable, typename>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator=(
    const Matrix<_core_other>& _other) {
  static_assert(Matrix<_core_impl>::rows == Matrix<_core_other>::rows &&
                    Matrix<_core_impl>::cols == Matrix<_core_other>::cols,
                "Error: dimension mismatch.");

  Matrix<_core_other> temp(_other);

  TraverseIndices(
      [&](std::size_t i, std::size_t j) { (*this)(i, j) = temp(i, j); });

  return *this;
}

template <typename _core_impl>
template <typename _expr, bool _enable, typename>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator=(const _expr& _e) {
  static_assert(rows == _expr::rows && cols == _expr::cols,
                "Error: dimension mismatch.");

  TraverseIndices(
      [&](std::size_t i, std::size_t j) { (*this)(i, j) = _e(i, j); });

  return *this;
}

template <typename _core_impl>
template <typename... Args, bool _enable, typename>
constexpr Matrix<_core_impl>::Matrix(Args&&... args)
    : _m_data(std::forward<Args>(args)...) {
  static_assert(
      std::is_constructible_v<_core_impl, Args&&...>,
      "Error: `_core_impl` is not constructible with the passed arguments.");
}

template <typename _core_impl>
constexpr typename Matrix<_core_impl>::size_type Matrix<_core_impl>::Rows()
    const {
  return rows;
}

template <typename _core_impl>
constexpr typename Matrix<_core_impl>::size_type Matrix<_core_impl>::Cols()
    const {
  return cols;
}

template <typename _core_impl>
constexpr Sglty::Core::Mode Matrix<_core_impl>::Mode() const {
  return core_mode;
}

template <typename _core_impl>
constexpr Sglty::Core::Major Matrix<_core_impl>::Major() const {
  return core_major;
}

template <typename _core_impl>
constexpr typename Matrix<_core_impl>::reference Matrix<_core_impl>::operator()(
    const size_type _row, const size_type _col) {
  return const_cast<reference>(std::as_const(*this).operator()(_row, _col));
}

template <typename _core_impl>
constexpr typename Matrix<_core_impl>::const_reference
Matrix<_core_impl>::operator()(const size_type _row,
                               const size_type _col) const {
  return _m_data.At(_row, _col);
}

template <typename _core_impl>
template <typename Func>
constexpr void Matrix<_core_impl>::TraverseIndices(Func&& fn) {
  std::as_const(*this).TraverseIndices(
      [&](size_type i, size_type j) { fn(i, j); });
}

template <typename _core_impl>
template <typename Func>
constexpr void Matrix<_core_impl>::TraverseIndices(Func&& fn) const {
  if constexpr (Major() == Core::Major::Row) {
    for (std::size_t i = 0; i < Rows(); i++) {
      for (std::size_t j = 0; j < Cols(); j++) {
        fn(i, j);
      }
    }
  } else {
    for (std::size_t j = 0; j < Cols(); j++) {
      for (std::size_t i = 0; i < Rows(); i++) {
        fn(i, j);
      }
    }
  }
}

template <typename _core_impl>
template <typename Func>
constexpr void Matrix<_core_impl>::TraverseValues(Func&& fn) {
  std::as_const(*this).TraverseValues([&](value_type val) { fn(val); });
}

template <typename _core_impl>
template <typename Func>
constexpr void Matrix<_core_impl>::TraverseValues(Func&& fn) const {
  if constexpr (Major() == Core::Major::Row) {
    for (std::size_t i = 0; i < Rows(); i++) {
      for (std::size_t j = 0; j < Cols(); j++) {
        fn((*this)(i, j));
      }
    }
  } else {
    for (std::size_t j = 0; j < Cols(); j++) {
      for (std::size_t i = 0; i < Rows(); i++) {
        fn((*this)(i, j));
      }
    }
  }
}

template <typename _core_impl>
template <typename _expr>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator+=(const _expr& _e) {
  static_assert(Traits::is_expression_v<_expr>, "Error: non-expression passed");
  static_assert(Matrix::rows == _expr::rows && Matrix::cols == _expr::cols,
                "Error: dimension mismatch.");

  TraverseIndices(
      [&](std::size_t i, std::size_t j) { (*this)(i, j) += _e(i, j); });
  return (*this);
}

template <typename _core_impl>
template <typename _scalar>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator*=(
    const _scalar _other) {
  static_assert(std::is_arithmetic_v<_scalar>,
                "Error: non-integral value passed.");

  TraverseIndices(
      [&](std::size_t i, std::size_t j) { (*this)(i, j) *= _other; });
  return (*this);
}

template <typename _core_impl>
template <typename _expr>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator-=(const _expr& _e) {
  static_assert(Traits::is_expression_v<_expr>, "Error: non-expression passed");
  static_assert(Matrix::rows == _expr::rows && Matrix::cols == _expr::cols,
                "Error: dimension mismatch.");

  return (*this) += -_e;
}

template <typename _core_impl>
void Matrix<_core_impl>::Print() const {
  for (size_type i = 0; i < Rows(); i++) {
    for (size_type j = 0; j < Cols(); j++) {
      std::cout << (*this)(i, j) << ' ';
    }
    std::cout << '\n';
  }
}

}  // namespace Sglty::Types

// Singularity/Types/Impl/Matrix.tpp
