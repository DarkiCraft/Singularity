#ifndef SINGULARITYLIB_MATRIX_DENSE_STORAGE_HPP
#define SINGULARITYLIB_MATRIX_DENSE_STORAGE_HPP

#include <array>

#include "StorageCore.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp, size_t _rows, size_t _cols, StorageOrdr _st_ordr>
class DenseStorage {
 public:
  using type_traits = TypeTraits<_Tp>;

  using value_type      = typename type_traits::value_type;
  using allocator_type  = typename type_traits::allocator_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  static constexpr size_t Rows() {
    return _rows;
  }
  static constexpr size_t Cols() {
    return _cols;
  }

  using storage_traits =
      StorageTraits<StorageType::Static, StorageMode::Dense, _st_ordr>;

  static constexpr StorageType StorageType() {
    return storage_traits::storage_type;
  }
  static constexpr StorageMode StorageMode() {
    return storage_traits::storage_mode;
  }
  static constexpr StorageOrdr StorageOrdr() {
    return storage_traits::storage_ordr;
  }

  constexpr inline reference At(const size_t _row, const size_t _col) {
    return _m_Get(_row, _col);
  }

  constexpr inline const_reference At(const size_t _row,
                                      const size_t _col) const {
    return const_cast<const_reference>(
        static_cast<const DenseStorage&>(*this).At(_row, _col));
  }

  constexpr inline pointer Data() {
    return _m_data.data();
  }
  constexpr inline const_pointer Data() const {
    return _m_data.data();
  }

 private:
  std::array<_Tp, _rows * _cols> _m_data;

  constexpr inline reference _m_Get(const size_t _row, const size_t _col) {
    if (StorageOrdr() == StorageOrdr::RowMajor) {
      return _m_data[_row * Cols() + _col];
    } else {
      return _m_data[_col * Rows() + _row];
    }
  }

  constexpr inline const_reference _m_Get(const size_t _row,
                                          const size_t _col) const {
    return const_cast<const_reference>(
        static_cast<const DenseStorage&>(*this)._m_Get(_row, _col));
  }
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_DENSE_STORAGE_HPP

// SingularityLib/Matrix/DenseStorage.hpp