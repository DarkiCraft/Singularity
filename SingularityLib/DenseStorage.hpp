#ifndef SINGULARITYLIB_DENSE_STORAGE_HPP
#define SINGULARITYLIB_DENSE_STORAGE_HPP

#include "StorageBase.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp,
          size_t _size,
          StorageType _st_type,
          StorageOrdr _st_ordr>
class DenseStorage : StorageBase<_Tp, _size, _st_type, _st_ordr> {
 public:
  using storage_traits =
      typename StorageBase<_Tp, _size, _st_type, _st_ordr>::storage_traits;
  using type_traits =
      typename StorageBase<_Tp, _size, _st_type, _st_ordr>::type_traits;

  static constexpr StorageType storage_type = storage_traits::storage_type;
  static constexpr StorageOrdr storage_ordr = storage_traits::storage_ordr;

  using value_type      = typename type_traits::value_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  constexpr inline size_t Size() const {
    return _size;
  }

  constexpr inline reference At(const size_t _index) override {
    return _m_data[_index];
  }
  constexpr inline const_reference At(const size_t _index) const override {
    return _m_data[_index];
  }

 private:
  std::array<_Tp, _size> _m_data;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_DENSE_STORAGE_HPP

// SingularityLib/DenseStorage.hpp