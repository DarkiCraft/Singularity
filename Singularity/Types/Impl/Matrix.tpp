#pragma once

#include "../Matrix.hpp"

#include <iostream>
#include <type_traits>
#include <utility>

#include "../../Traits/Expr.hpp"
#include "../../Op/Arthm/Neg.hpp"

namespace Sglty::Types {

template <typename _core_impl>
template <typename _core_other, bool _enable, typename>
constexpr Matrix<_core_impl>::Matrix(const Matrix<_core_other>& _other) {
  static_assert(std::is_convertible_v<typename _core_other::value_type,
                                      typename core_impl::value_type>,
                "Error: cannot convert `_core_other::value_type` to "
                "`core_impl::value_type`.");
  static_assert(
      Matrix<core_impl>::rows == Matrix<_core_other>::rows &&
          Matrix<core_impl>::cols == Matrix<_core_other>::cols,
      "Error: dimension mismatch between `core_impl` and `_core_other`.");

  Traverse(*this,
           [&](std::size_t i, std::size_t j) { (*this)(i, j) = _other(i, j); });
}

template <typename _core_impl>
template <typename _expr, bool _enable, typename>
constexpr Matrix<_core_impl>::Matrix(const _expr& _e) {
  static_assert(
      std::is_same_v<typename Matrix::core_impl, typename _expr::core_impl>,
      "Error: `core_impl` mismatch.");

  Traverse(*this,
           [&](std::size_t i, std::size_t j) { (*this)(i, j) = _e(i, j); });
}

template <typename _core_impl>
template <typename _core_other, bool _enable, typename>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator=(
    const Matrix<_core_other>& _other) {
  static_assert(Matrix<core_impl>::rows == Matrix<_core_other>::rows &&
                    Matrix<core_impl>::cols == Matrix<_core_other>::cols,
                "Error: dimension mismatch.");

  Matrix<_core_other> temp(_other);

  Traverse(*this,
           [&](std::size_t i, std::size_t j) { (*this)(i, j) = temp(i, j); });

  return *this;
}

template <typename _core_impl>
template <typename _expr, bool _enable, typename>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator=(const _expr& _e) {
  static_assert(rows == _expr::rows && cols == _expr::cols,
                "Error: dimension mismatch.");

  Traverse(*this,
           [&](std::size_t i, std::size_t j) { (*this)(i, j) = _e(i, j); });

  return *this;
}

template <typename _core_impl>
template <typename... Args, bool _enable, typename>
constexpr Matrix<_core_impl>::Matrix(Args&&... args)
    : _m_data(std::forward<Args>(args)...) {
  static_assert(
      std::is_constructible_v<core_impl, Args&&...>,
      "Error: `core_impl` is not constructible with the passed arguments.");
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
constexpr Sglty::Core::Type Matrix<_core_impl>::Type() const {
  return core_type;
}

template <typename _core_impl>
constexpr Sglty::Core::Major Matrix<_core_impl>::Major() const {
  return core_major;
}

template <typename _core_impl>
template <typename _Up>
constexpr Matrix<typename _core_impl::core_rebind_value<_Up>>
Matrix<_core_impl>::Cast() const {
  static_assert(std::is_arithmetic_v<_Up>,
                "Error: cannot cast to a non-arithmetic type.");

  using result_core = typename core_impl::core_rebind_value<_Up>;

  Matrix<result_core> result;
  Traverse(result, [&](std::size_t i, std::size_t j) {
    result(i, j) = static_cast<_Up>((*this)(i, j));
  });
  return result;
}

template <typename _core_impl>
template <Core::Major _major>
constexpr Matrix<typename _core_impl::core_rebind_major<_major>>
Matrix<_core_impl>::Reorder() const {
  {
    Traits::Core::Get<core_type,
                      _major>
        _;  // to assert correctness of new major
  }

  using result_core = typename core_impl::core_rebind_major<_major>;

  Matrix<result_core> result;
  Traverse(result,
           [&](std::size_t i, std::size_t j) { result(i, j) = (*this)(i, j); });
  return result;
}

template <typename _core_impl>
constexpr Matrix<_core_impl> Matrix<_core_impl>::Zero() {
  Matrix<_core_impl> result;
  Traverse(result, [&](std::size_t i, std::size_t j) { result(i, j) = 0; });
  return result;
}

template <typename _core_impl>
constexpr Matrix<_core_impl> Matrix<_core_impl>::Identity() {
  static_assert(Matrix<core_impl>::rows == Matrix<core_impl>::cols,
                "Error: an Identity matrix must be a square matrix.");
  Matrix<core_impl> result;
  for (size_type i = 0; i < Matrix<core_impl>::rows; i++) {
    result(i, i) = Matrix<core_impl>::value_type(1);
  }
  return result;
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
template <typename _expr>
constexpr Matrix<_core_impl>& Matrix<_core_impl>::operator+=(const _expr& _e) {
  static_assert(Traits::Expr::is_valid_v<_expr>,
                "Error: non-expression passed");
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
  static_assert(Traits::Expr::is_valid_v<_expr>,
                "Error: non-expression passed");
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

namespace Impl {

template <typename Func>
constexpr void Traverse(std::size_t rows,
                        std::size_t cols,
                        Func&& fn,
                        Core::Major major) {
  if (major == Core::Major::Row) {
    for (std::size_t i = 0; i < rows; i++) {
      for (std::size_t j = 0; j < cols; j++) {
        fn(i, j);
      }
    }
  } else {
    for (std::size_t j = 0; j < cols; j++) {
      for (std::size_t i = 0; i < rows; i++) {
        fn(i, j);
      }
    }
  }
}

}  // namespace Impl

template <typename _core_impl, typename Func>
constexpr void Traverse(Matrix<_core_impl>& mat, Func&& fn) {
  Impl::Traverse(mat.Rows(), mat.Cols(), std::forward<Func>(fn), mat.Major());
}

template <typename _core_impl, typename Func>
constexpr void Traverse(const Matrix<_core_impl>& mat, Func&& fn) {
  Impl::Traverse(mat.Rows(), mat.Cols(), std::forward<Func>(fn), mat.Major());
}

}  // namespace Sglty::Types

// Singularity/Types/Impl/Matrix.tpp
