#pragma once

#include <type_traits>

#include "../Expr/Tag.hpp"
#include "../Traits/Core.hpp"
#include "../Traits/Expr.hpp"

namespace Sglty::Types {

/**
 * @brief Compile-time matrix wrapper for a core implementation.
 *
 * `Matrix` acts as the primary user-facing type for working with matrices in
 * Singularity. It wraps a user-defined `_core_impl` type which must satisfy a
 * fixed interface using trait checks, namely:
 *
 * - `Sglty::Traits::Core::has_size_traits_v`
 *
 * - `Sglty::Traits::Core::has_type_traits_v`
 *
 * - `Sglty::Traits::Core::has_core_traits_v`
 *
 * - `Sglty::Traits::Core::has_rebind_size_traits_v`
 *
 * - `Sglty::Traits::Core::has_member_functions_v`
 *
 * Usage:
 * ```
 * using core = SomeCoreImpl<...>;
 * Sglty::Types::Matrix<core> mat;
 * ```
 *
 * Can also be constructed from:
 *
 * - Other compatible `Matrix<_core_impl>` types
 *
 * - Expression types satisfying `Sglty::Traits::Expr::is_valid_v`
 *
 * @tparam _core_impl The core implementation backing the matrix data.
 */
template <typename _core_impl>
class Matrix : public Expr::Tag {
  static_assert(std::is_default_constructible_v<_core_impl>,
                "Error: `_core_impl` must be default constructible.");

  static_assert(Traits::Core::has_size_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `size_traits`.");

  static_assert(Traits::Core::has_type_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `type_traits`.");

  static_assert(Traits::Core::has_core_traits_v<_core_impl>,
                "Error: `_core_impl` must define nested type `core_traits`.");

  static_assert(
      _core_impl::size_traits::rows > 0 && _core_impl::size_traits::cols > 0,
      "Error: `size_traits::rows` and `size_traits:cols` must be positive.");

  static_assert(Traits::Core::has_rebind_size_traits_v<_core_impl>,
                "Error: `_core_impl` must define rebinding traits.");

  static_assert(Traits::Core::has_member_functions_v<_core_impl>,
                "Error: `_core_impl` must provide member functions `At()` and "
                "`Data()` with correct signatures and return types.");

  template <typename>
  friend class Matrix;

 public:
  /**
   * @brief The core implementation backing this Matrix.
   *
   * This defines the actual storage and operation logic.
   * Must satisfy core interface traits as validated by static_asserts.
   */
  using core_impl = _core_impl;

  /**
   * @brief Traits describing the value type and associated aliases.
   *
   * Extracted from `core_impl::type_traits`, this includes typedefs for
   * size, value, references, and pointers used throughout the matrix API.
   */
  using type_traits = typename core_impl::type_traits;

  /// The type used to represent sizes (rows, cols, strides).
  using size_type = typename type_traits::size_type;

  /// The value type stored in the matrix.
  using value_type = typename type_traits::value_type;

  /// Signed type for indexing differences.
  using difference_type = typename type_traits::difference_type;

  /// Mutable reference to a matrix element.
  using reference = typename type_traits::reference;

  /// Const reference to a matrix element.
  using const_reference = typename type_traits::const_reference;

  /// Pointer to the matrix element type.
  using pointer = typename type_traits::pointer;

  /// Const pointer to the matrix element type.
  using const_pointer = typename type_traits::const_pointer;

  /**
   * @brief Compile-time traits describing matrix dimensions.
   *
   * Typically contains static constants `rows` and `cols`.
   */
  using size_traits = typename core_impl::size_traits;

  /// Number of rows in the matrix (compile-time constant).
  constexpr static auto rows = size_traits::rows;

  /// Number of columns in the matrix (compile-time constant).
  constexpr static auto cols = size_traits::cols;

  /**
   * @brief Compile-time traits describing core metadata.
   *
   * Includes the memory layout and the type identifier of the core.
   */
  using core_traits = typename core_impl::core_traits;

  /// The core type enum (e.g., `Core::Type::Dense`, etc.)
  constexpr static auto core_type = core_traits::core_type;

  /// The memory layout of the matrix (e.g., row-major or column-major).
  constexpr static auto core_major = core_traits::core_major;

  /**
   * @brief Default-constructs a Matrix.
   *
   * Constructs a Matrix with a default-initialized core implementation.
   * All underlying storage is zero-initialized by the core.
   */
  constexpr Matrix() = default;

  /**
   * @brief Copy-constructs a Matrix from another instance.
   *
   * Performs a shallow copy of the underlying core.
   */
  constexpr Matrix(const Matrix& _other) = default;

  /**
   * @brief Move-constructs a Matrix from another instance.
   *
   * Moves the underlying core, leaving `_other` in a valid but unspecified
   * state.
   */
  constexpr Matrix(Matrix&& _other) noexcept = default;

  /**
   * @brief Copy-assigns from another Matrix.
   *
   * Performs a shallow copy of the underlying core.
   *
   * @return Reference to the current Matrix.
   */
  constexpr Matrix& operator=(const Matrix& _other) = default;

  /**
   * @brief Move-assigns from another Matrix.
   *
   * Moves the underlying core, leaving `_other` in a valid but unspecified
   * state.
   *
   * @return Reference to the current Matrix.
   */
  constexpr Matrix& operator=(Matrix&& _other) noexcept = default;

  /**
   * @brief Constructs a Matrix from another Matrix with a different core
   * implementation.
   *
   * This constructor allows conversion between compatible `Matrix` types
   * backed by different `_core_impl` types. Enabled only if the other core
   * type is not the same as the current one.
   *
   * The core implementations must define matching dimensions and compatible
   * traits for this to compile successfully.
   *
   * @tparam _core_other The core implementation of the source Matrix.
   * @param _other The source Matrix to copy from.
   */
  template <typename _core_other,
            bool _enable = !std::is_same_v<core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const Matrix<_core_other>& _other);

  /**
   * @brief Constructs a Matrix from a valid expression type.
   *
   * This constructor enables initializing a `Matrix` from any expression
   * type that satisfies `Sglty::Traits::Expr::is_valid_v<T>`.
   *
   * Useful for creating a concrete matrix from compile-time expression trees,
   * such as the result of arithmetic operations between matrices.
   *
   * Enabled only if `_expr` is a valid expression.
   *
   * @tparam _expr The expression type to construct from.
   * @param _e The expression to evaluate into a Matrix.
   */
  template <typename _expr,
            bool _enable = Traits::Expr::is_valid_v<std::decay_t<_expr>>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix(const _expr& _e);

  /**
   * @brief Assigns from another Matrix with a different core implementation.
   *
   * Allows assigning between `Matrix` instances backed by different
   * `_core_impl` types, provided they are compatible in dimensions and traits.
   *
   * Enabled only if the other core type is not the same.
   *
   * @tparam _core_other The core implementation of the source Matrix.
   * @param _other The source Matrix to assign from.
   * @return Reference to the current Matrix.
   */
  template <typename _core_other,
            bool _enable = !std::is_same_v<core_impl, _core_other>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix& operator=(const Matrix<_core_other>& _other);

  /**
   * @brief Assigns from a valid expression type.
   *
   * Evaluates the expression and stores the result in the current Matrix.
   * The expression must satisfy `Sglty::Traits::Expr::is_valid_v`.
   *
   * Enabled only if `_expr` is a valid expression type.
   *
   * @tparam _expr The expression type.
   * @param _e The expression to evaluate and assign.
   * @return Reference to the current Matrix.
   */
  template <typename _expr,
            bool _enable = Traits::Expr::is_valid_v<std::decay_t<_expr>>,
            typename     = std::enable_if_t<_enable>>
  constexpr Matrix& operator=(const _expr& _e);

  /**
   * @brief Constructs a Matrix by forwarding arguments to the core
   * implementation.
   *
   * This constructor forwards the provided arguments to construct the
   * underlying `_core_impl`. It is enabled only if:
   *
   * - At least one argument is passed, and
   *
   * - The arguments do **not** match Matrix copy/move/expr constructor
   * patterns.
   *
   * This allows users to directly construct the core with custom initialization
   * logic, giving full control over how the matrix is initialized.
   *
   * A static assertion ensures that `_core_impl` is constructible from the
   * provided arguments.
   *
   * @tparam Args Argument types used to initialize the core.
   * @param args Arguments forwarded to `_core_impl`.
   */
  template <typename... Args,
            bool _enable = sizeof...(Args) != 0 &&
                           !(sizeof...(Args) == 1 &&
                             ((std::is_same_v<std::decay_t<Args>, Matrix> ||
                               Traits::Expr::is_valid_v<std::decay_t<Args>>) ||
                              ...)),
            typename = std::enable_if_t<_enable>>
  constexpr explicit Matrix(Args&&... args);

  /**
   * @brief Returns the number of rows in the matrix.
   *
   * @return The number of rows as a constant expression.
   */
  constexpr size_type Rows() const;

  /**
   * @brief Returns the number of columns in the matrix.
   *
   * @return The number of columns as a constant expression.
   */
  constexpr size_type Cols() const;

  /**
   * @brief Returns the core storage type tag.
   *
   * Typically used to distinguish between different core implementations
   * (e.g., dense vs sparse) during compile-time.
   *
   * @return The core type tag defined in `core_traits`.
   */
  constexpr Sglty::Core::Type Type() const;

  /**
   * @brief Returns the memory layout order of the matrix.
   *
   * Indicates whether the matrix uses row-major or column-major layout.
   * The value is defined by the core’s `core_traits`.
   *
   * @return The memory layout major.
   */
  constexpr Sglty::Core::Major Major() const;

  /**
   * @brief Casts the matrix to a different value type.
   *
   * Rebinds the underlying core implementation to use the new value type `_Up`,
   * preserving all other core traits like size and layout.
   *
   * @tparam _Up The new value type.
   * @return A new Matrix with the same shape and layout, but different value
   * type.
   */
  template <typename _Up>
  constexpr Matrix<typename core_impl::core_rebind_value<_Up>> Cast() const;

  /**
   * @brief Reorders the matrix to a different memory layout (row-major or
   * column-major).
   *
   * Rebinds the core implementation to use the new memory layout specified
   * by `_major`. Actual layout handling is delegated to the core
   * implementation.
   *
   * @tparam _major The new layout order (row-major or column-major).
   * @return A new Matrix with the reordered layout.
   */
  template <Core::Major _major>
  constexpr Matrix<typename core_impl::core_rebind_major<_major>> Reorder()
      const;

  /**
   * @brief Returns a zero-initialized matrix.
   *
   * Constructs a matrix of the same type and size with all elements set to
   * zero. The implementation is handled manually by the `Matrix` class.
   *
   * @return A zero matrix.
   */
  constexpr static Matrix Zero();

  /**
   * @brief Returns the identity matrix.
   *
   * Constructs an identity matrix of the same shape, where diagonal elements
   * are one and all others are zero. The implementation is handled manually.
   *
   * Only meaningful for square matrices — compiler error otherwise.
   *
   * @return An identity matrix.
   */
  constexpr static Matrix Identity();

  /**
   * @brief Accesses a mutable element at the specified position.
   *
   * @param _row The row index (zero-based).
   * @param _col The column index (zero-based).
   * @return Reference to the element at (_row, _col).
   */
  constexpr reference operator()(const size_type _row, const size_type _col);

  /**
   * @brief Accesses a read-only element at the specified position.
   *
   * @param _row The row index (zero-based).
   * @param _col The column index (zero-based).
   * @return Const reference to the element at (_row, _col).
   */
  constexpr const_reference operator()(const size_type _row,
                                       const size_type _col) const;

  /**
   * @brief Adds a valid expression to the matrix.
   *
   * Performs element-wise addition with another matrix or expression
   * satisfying `Sglty::Traits::Expr::is_valid_v`.
   *
   * @tparam _expr The expression type.
   * @param _e The expression to add.
   * @return Reference to the current matrix after modification.
   */
  template <typename _expr>
  constexpr Matrix& operator+=(const _expr& _e);

  /**
   * @brief Multiplies the matrix by a scalar value.
   *
   * Performs element-wise scaling of the matrix by `_other`.
   * Enabled only for arithmetic scalar types.
   *
   * @tparam _scalar The scalar type (must satisfy `std::is_arithmetic`).
   * @param _other The scalar value to multiply.
   * @return Reference to the current matrix after scaling.
   */
  template <typename _scalar>
  constexpr Matrix& operator*=(const _scalar _other);

  /**
   * @brief Subtracts a valid expression from the matrix.
   *
   * Performs element-wise subtraction with another matrix or expression
   * satisfying `Sglty::Traits::Expr::is_valid_v`.
   *
   * @tparam _expr The expression type.
   * @param _e The expression to subtract.
   * @return Reference to the current matrix after modification.
   */
  template <typename _expr>
  constexpr Matrix& operator-=(const _expr& _e);

  // temporary for tests
  void Print() const;

 private:
  core_impl _m_data{};
};

/**
 * @brief Applies a function to each element in the matrix (mutable version).
 *
 * Iterates over the matrix in row-major order and applies `fn` to each
 * element reference. The function must accept a single reference argument.
 *
 * @tparam _core_impl The core implementation backing the Matrix.
 * @tparam Func The callable type accepting `reference`.
 * @param mat The matrix to traverse.
 * @param fn The function to apply to each element.
 */
template <typename _core_impl, typename Func>
constexpr void Traverse(Matrix<_core_impl>& mat, Func&& fn);

/**
 * @brief Applies a function to each element in the matrix (const version).
 *
 * Iterates over the matrix in row-major order and applies `fn` to each
 * element as a const reference. The function must accept a const reference.
 *
 * @tparam _core_impl The core implementation backing the Matrix.
 * @tparam Func The callable type accepting `const_reference`.
 * @param mat The matrix to traverse.
 * @param fn The function to apply to each element.
 */
template <typename _core_impl, typename Func>
constexpr void Traverse(const Matrix<_core_impl>& mat, Func&& fn);

}  // namespace Sglty::Types

#include "Impl/Matrix.tpp"

// Singularity/Types/Matrix.hpp
