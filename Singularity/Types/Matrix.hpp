#pragma once

#include <type_traits>

#include "../Expr/Tag.hpp"
#include "../Traits/Core.hpp"
#include "../Traits/Expr.hpp"

namespace Sglty::Types {

template <typename _core_impl>
class Matrix : public Expr::Tag {
  static_assert(Traits::Core::has_size_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `size_traits`.");

  static_assert(Traits::Core::has_type_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `type_traits`.");

  static_assert(Traits::Core::has_core_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `core_traits`.");

  static_assert(
      _core_impl::size_traits::rows > 0 && _core_impl::size_traits::cols > 0,
      "Error: `size_traits::rows` and `size_traits:cols` must be positive.");

  static_assert(Traits::Core::has_member_functions_v<_core_impl>,
                "Error: `_core_impl` must provide member functions `At()` and "
                "`Data()` with correct signatures and return types.");

  template <typename>
  friend class Matrix;

 public:
  using type_traits = typename _core_impl::type_traits;

  using size_type       = typename type_traits::size_type;
  using value_type      = typename type_traits::value_type;
  using difference_type = typename type_traits::difference_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  using size_traits = typename _core_impl::size_traits;

  constexpr static auto rows = size_traits::rows;
  constexpr static auto cols = size_traits::cols;

  using core_traits = typename _core_impl::core_traits;

  constexpr static auto core_type  = core_traits::core_type;
  constexpr static auto core_major = core_traits::core_major;

  using core_impl = _core_impl;

  Matrix();

  constexpr Matrix(const Matrix& _other)     = default;
  constexpr Matrix(Matrix&& _other) noexcept = default;

  template <typename _core_other,
            bool _enable = !std::is_same_v<_core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const Matrix<_core_other>& _other);

  template <typename _expr,
            bool _enable = Traits::Expr::is_valid_v<std::decay_t<_expr>>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const _expr& _e);

  constexpr Matrix& operator=(const Matrix& _other)     = default;
  constexpr Matrix& operator=(Matrix&& _other) noexcept = default;

  template <typename _core_other,
            bool _enable = !std::is_same_v<_core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix& operator=(const Matrix<_core_other>& _other);

  template <typename _expr,
            bool _enable = Traits::Expr::is_valid_v<std::decay_t<_expr>>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix& operator=(const _expr& _e);

  template <typename... Args,
            bool _enable = sizeof...(Args) != 0 &&
                           !(sizeof...(Args) == 1 &&
                             ((std::is_same_v<std::decay_t<Args>, Matrix> ||
                               Traits::Expr::is_valid_v<std::decay_t<Args>>) ||
                              ...)),
            typename = std::enable_if_t<_enable>>
  constexpr explicit Matrix(Args&&... args);

  constexpr size_type Rows() const;
  constexpr size_type Cols() const;

  constexpr Sglty::Core::Type Type() const;
  constexpr Sglty::Core::Major Major() const;

  constexpr reference operator()(const size_type _row, const size_type _col);
  constexpr const_reference operator()(const size_type _row,
                                       const size_type _col) const;

  template <typename _expr>
  constexpr Matrix& operator+=(const _expr& _e);

  template <typename _scalar>
  constexpr Matrix& operator*=(const _scalar _other);

  template <typename _expr>
  constexpr Matrix& operator-=(const _expr& _e);

  constexpr static Matrix Zero();

  constexpr static Matrix Identity();

  // temporary for tests
  void Print() const;

 private:
  _core_impl _m_data;
};

template <typename _core_impl, typename Func>
constexpr void Traverse(Matrix<_core_impl>& mat, Func&& fn);

template <typename _core_impl, typename Func>
constexpr void Traverse(const Matrix<_core_impl>& mat, Func&& fn);

}  // namespace Sglty::Types

#include "Impl/Matrix.tpp"

// Singularity/Types/Matrix.hpp
