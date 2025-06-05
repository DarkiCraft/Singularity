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
  using type_traits = TypeTraits<_Tp>;

  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  using core_traits = CoreTraits<CoreMode::Dense, _core_ordr>;

  DenseCore() = default;

  static constexpr size_t Rows() {
    return _rows;
  }
  static constexpr size_t Cols() {
    return _cols;
  }

  // static constexpr CoreMode CoreMode() {
  //   return core_traits::core_mode;
  // }
  // static constexpr CoreOrdr CoreOrdr() {
  //   return core_traits::core_ordr;
  // }

  constexpr inline reference At(const size_t _row, const size_t _col) {
    return const_cast<reference>(std::as_const(*this).At(_row, _col));
  }

  constexpr inline const_reference At(const size_t _row,
                                      const size_t _col) const {
    return _m_Get(_row, _col);
  }

  constexpr inline pointer Data() {
    return const_cast<pointer>(std::as_const(*this).Data());
  }

  constexpr inline const_pointer Data() const {
    return _m_data.data();
  }

 private:
  std::array<_Tp, Rows() * Cols()> _m_data;

  constexpr inline reference _m_Get(const size_t _row, const size_t _col) {
    return const_cast<reference>(std::as_const(*this)._m_Get(_row, _col));
  }

  constexpr inline const_reference _m_Get(const size_t _row,
                                          const size_t _col) const {
    if (CoreOrdr() == CoreOrdr::RowMajor) {
      return _m_data[_row * Cols() + _col];
    } else {
      return _m_data[_col * Rows() + _row];
    }
  }
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_CORE_DENSE_HPP

// SingularityLib/Matrix/Core/Dense.hpp