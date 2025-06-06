#ifndef SINGULARITYLIB_MATRIX_CORE_DENSE_HPP
#define SINGULARITYLIB_MATRIX_CORE_DENSE_HPP

#include <array>
#include <utility>
#include <vector>

#include "Checks.hpp"

using std::size_t;

namespace Sglty {

template <typename _Tp, size_t _rows, size_t _cols, CoreOrdr _core_ordr>
class DenseCore {
 public:
  using size_traits = SizeTraits<_rows, _cols>;

  using type_traits = TypeTraits<_Tp>;

  using core_traits = CoreTraits<CoreMode::Dense, _core_ordr>;

  template <size_t _rebind_rows, size_t _rebind_cols>
  using core_rebind =
      DenseCore<_Tp, _rebind_rows, _rebind_cols, core_traits::core_ordr>;

  using core_base = DenseCore<_Tp, 0, 0, core_traits::core_ordr>;

  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  DenseCore() = default;

  constexpr reference At(const size_t _row, const size_t _col) {
    return const_cast<reference>(std::as_const(*this).At(_row, _col));
  }
  constexpr const_reference At(const size_t _row, const size_t _col) const {
    return _m_Get(_row, _col);
  }

  constexpr pointer Data() {
    return const_cast<pointer>(std::as_const(*this).Data());
  }
  constexpr const_pointer Data() const {
    return _m_data.data();
  }

 private:
  std::array<_Tp, _rows * _cols> _m_data;

  constexpr inline reference _m_Get(const size_t _row, const size_t _col) {
    return const_cast<reference>(std::as_const(*this)._m_Get(_row, _col));
  }
  constexpr inline const_reference _m_Get(const size_t _row,
                                          const size_t _col) const {
    if (core_traits::core_ordr == CoreOrdr::RowMajor) {
      return _m_data[_row * _cols + _col];
    } else {
      return _m_data[_col * _rows + _row];
    }
  }
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_CORE_DENSE_HPP

// SingularityLib/Matrix/Core/Dense.hpp