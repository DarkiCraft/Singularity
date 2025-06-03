#ifndef SINGULARITYLIB_MATRIX_CORE_DENSE_HPP
#define SINGULARITYLIB_MATRIX_CORE_DENSE_HPP

#include <array>
#include <vector>

#include "Checks.hpp"

using size_t = unsigned long long;

namespace Sglty {

inline constexpr size_t DENSE_CORE_DYNAMIC = 0;

template <typename _Tp, size_t _rows, size_t _cols, CoreOrdr _core_ordr>
class DenseCore {
  static constexpr bool _m_is_rows_dynamic = _rows == DENSE_CORE_DYNAMIC;
  static constexpr bool _m_is_cols_dynamic = _cols == DENSE_CORE_DYNAMIC;
  static constexpr bool _m_is_core_dynamic =
      _m_is_rows_dynamic || _m_is_cols_dynamic;

 public:
  using type_traits = TypeTraits<_Tp>;

  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  constexpr size_t Rows() {
    return _m_rows;
  }
  constexpr size_t Cols() {
    return _m_cols;
  }

  using core_traits =
      CoreTraits<_m_is_core_dynamic ? CoreType::Dynamc : CoreType::Static,
                 CoreMode::Dense,
                 _core_ordr>;

  static constexpr CoreType CoreType() {
    return core_traits::core_type;
  }
  static constexpr CoreMode CoreMode() {
    return core_traits::core_mode;
  }
  static constexpr CoreOrdr CoreOrdr() {
    return core_traits::core_ordr;
  }

  constexpr inline reference At(const size_t _row, const size_t _col) {
    return _m_Get(_row, _col);
  }

  constexpr inline const_reference At(const size_t _row,
                                      const size_t _col) const {
    return const_cast<const_reference>(
        static_cast<const DenseCore&>(*this).At(_row, _col));
  }

  constexpr inline pointer Data() {
    return _m_data.data();
  }

  constexpr inline const_pointer Data() const {
    return const_cast<const_pointer>(
        static_cast<const DenseCore&>(*this).Data());
  }

 private:
  using _m_ContainerType = std::conditional_t<_m_is_core_dynamic,
                                              std::vector<_Tp>,
                                              std::array<_Tp, _rows * _cols>>;

  size_t _m_rows = _rows;
  size_t _m_cols = _cols;

  _m_ContainerType _m_data;

  constexpr inline reference _m_Get(const size_t _row, const size_t _col) {
    if (CoreOrdr() == CoreOrdr::RowMajor) {
      return _m_data[_row * Cols() + _col];
    } else {
      return _m_data[_col * Rows() + _row];
    }
  }

  constexpr inline const_reference _m_Get(const size_t _row,
                                          const size_t _col) const {
    return const_cast<const_reference>(
        static_cast<const DenseCore&>(*this)._m_Get(_row, _col));
  }
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_CORE_DENSE_HPP

// SingularityLib/Matrix/Core/Dense.hpp