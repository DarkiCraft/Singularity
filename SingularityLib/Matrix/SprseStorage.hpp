#ifndef SINGULARITYLIB_SPRSE_MATRIX_STORAGE_HPP
#define SINGULARITYLIB_SPRSE_MATRIX_STORAGE_HPP

#include <unordered_map>
#include <utility>
#include <vector>

#include "StorageCore.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp, size_t _rows, size_t _cols>
class SprseStorage {
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

  using storage_traits = StorageTraits<StorageType::Static,
                                       StorageMode::Sprse,
                                       StorageOrdr::Udefined>;

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
    return _m_dummy_val;
  }
  constexpr inline const_reference At(const size_t _row,
                                      const size_t _col) const {
    return _m_dummy_val;
  }

  constexpr inline pointer Data() {
    return nullptr;
  }
  constexpr inline const_pointer Data() const {
    return nullptr;
  }

 private:
  struct m_pair_hash {
    size_t operator()(const std::pair<size_t, size_t>& pair) const {
      auto hash_a = std::hash<size_t>{}(pair.first);
      auto hash_b = std::hash<size_t>{}(pair.second);
      return hash_a ^ (hash_b << 1);
    }
  };

  std::vector<value_type> _m_data;
  std::unordered_map<std::pair<size_t, size_t>, size_t, m_pair_hash> _m_indices;

  static constexpr value_type _m_dummy_val = 0;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_SPRSE_STORAGE_HPP

// SinularityLib/Matrix/SprseStorage.hpp