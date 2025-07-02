#pragma once

#include <cstddef>
#include <array>

#include "Enums.hpp"
#include "../Traits/Type.hpp"
#include "../Traits/Size.hpp"
#include "../Traits/Core.hpp"

namespace Sglty::Core {

/**
 * @brief Fixed-size, compile-time dense matrix core.
 *
 * `Dense` provides a memory-efficient, flat array-backed storage for
 * statically sized matrices. It is designed for full compile-time operation
 * and integrates cleanly with the `Matrix` wrapper in Singularity.
 *
 * This class defines the standard interface expected of a core implementation:
 *
 * - Static size traits via `size_traits`
 * - Type aliases and traits via `type_traits`
 * - Member accessors `At()` and `Data()`
 * - Rebinding mechanisms for size, value type, and memory layout
 *
 * Intended for small to medium-sized matrices that benefit from aggressive
 * compile-time optimization and layout control.
 *
 * @tparam _Tp         The scalar element type.
 * @tparam _rows       The number of rows in the matrix.
 * @tparam _cols       The number of columns in the matrix.
 * @tparam _core_major The memory layout (row-major or column-major).
 */
template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
class Dense {
 public:
  /// Type traits for the matrix element type.
  using type_traits = Traits::Type::Get<_Tp>;

  using size_type       = typename type_traits::size_type;
  using value_type      = typename type_traits::value_type;
  using difference_type = typename type_traits::difference_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  /// Size traits defining row and column dimensions.
  using size_traits = Traits::Size::Get<_rows, _cols, size_type>;

  /// Core trait describing layout and type identity.
  using core_traits = Traits::Core::Get<Core::Type::Dense, _core_major>;

  /**
   * @brief Rebinds the Dense core to a new size.
   *
   * Useful when resizing expressions or transforming to a differently sized
   * but structurally similar matrix.
   *
   * @tparam _rebind_rows New row count.
   * @tparam _rebind_cols New column count.
   */
  template <size_type _rebind_rows, size_type _rebind_cols>
  using core_rebind_size =
      Dense<_Tp, _rebind_rows, _rebind_cols, core_traits::core_major>;

  /**
   * @brief Rebinds the Dense core to a new value type.
   *
   * Typically used for casting matrices to another scalar type.
   *
   * @tparam _rebind_value The new value type.
   */
  template <typename _rebind_value>
  using core_rebind_value =
      Dense<_rebind_value, _rows, _cols, core_traits::core_major>;

  /**
   * @brief Rebinds the Dense core to a different memory layout.
   *
   * Preserves size and type but switches between row-major and column-major.
   *
   * @tparam _rebind_major The new layout.
   */
  template <Core::Major _rebind_major>
  using core_rebind_major = Dense<_Tp, _rows, _cols, _rebind_major>;

  /**
   * @brief Alias to a zero-sized base version of Dense with the same layout.
   *
   * Often used for compile-time type operations or defaults.
   */
  using core_base = Dense<_Tp, 0, 0, core_traits::core_major>;

  /**
   * @brief Default-constructs the Dense core with zero-initialized data.
   *
   * The internal array is value-initialized.
   */
  constexpr Dense() = default;

  /**
   * @brief Constructs a Dense core with all elements initialized to a value.
   *
   * @param val The value to fill every element with.
   */
  constexpr Dense(value_type val);

  /**
   * @brief Accesses a mutable reference to the element at (_row, _col).
   *
   * @param _row The row index (zero-based).
   * @param _col The column index (zero-based).
   * @return Reference to the element.
   */
  constexpr reference At(const size_type _row, const size_type _col);

  /**
   * @brief Accesses a read-only reference to the element at (_row, _col).
   *
   * @param _row The row index (zero-based).
   * @param _col The column index (zero-based).
   * @return Const reference to the element.
   */
  constexpr const_reference At(const size_type _row,
                               const size_type _col) const;

  /**
   * @brief Returns a raw pointer to the underlying data array.
   *
   * @return Mutable pointer to the matrix data.
   */
  constexpr pointer Data();

  /**
   * @brief Returns a const raw pointer to the underlying data array.
   *
   * @return Const pointer to the matrix data.
   */
  constexpr const_pointer Data() const;

 private:
  std::array<_Tp, _rows * _cols> _m_data{};

  constexpr reference _m_Get(const size_type _row, const size_type _col);
  constexpr const_reference _m_Get(const size_type _row,
                                   const size_type _col) const;
};

}  // namespace Sglty::Core

#include "Impl/Dense.tpp"

// Singularity/Core/Dense.hpp
