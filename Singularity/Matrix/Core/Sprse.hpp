#ifndef SINGULARITY_MATRIX_CORE_SPRSE_HPP
#define SINGULARITY_MATRIX_CORE_SPRSE_HPP

#include <unordered_map>
#include <utility>
#include <vector>

#include "Checks.hpp"

using std::size_t;

namespace Sglty {

template <typename _Tp, size_t _rows, size_t _cols>
class SprseCore {
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

  using core_traits = CoreTraits<CoreMode::Sprse, CoreOrdr::Udefined>;

  static constexpr CoreMode CoreMode() {
    return core_traits::core_mode;
  }
  static constexpr CoreOrdr CoreOrdr() {
    return core_traits::core_ordr;
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

#endif  // SINGULARITY_MATRIX_CORE_SPRSE_HPP

// Sinularity/Matrix/Core/Sprse.hpp