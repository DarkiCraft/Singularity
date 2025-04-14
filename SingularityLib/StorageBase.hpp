#ifndef SINGULARITYLIB_STORAGE_BASE_HPP
#define SINGULARITYLIB_STORAGE_BASE_HPP

#include <array>
#include <type_traits>

#include "StorageTraits.hpp"
#include "TypeTraits.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _Tp,
          size_t _size,
          StorageType _st_type,
          StorageOrdr _st_ordr>
class StorageBase {
 public:
  static_assert(std::is_arithmetic_v<_Tp>, "_Tp must be an arithmetic type");
  static_assert(_size > 0, "_size must be > 0");
  static_assert(is_valid_storage_trait_v<_st_type, _st_ordr>,
                "Invalid StorageTraits<> Combination.");

  using storage_traits = StorageTraits<_st_type, _st_ordr>;
  using type_traits    = TypeTraits<_Tp>;

  static constexpr StorageType storage_type = storage_traits::storage_type;
  static constexpr StorageOrdr storage_ordr = storage_traits::storage_ordr;

  using value_type      = typename type_traits::value_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  static constexpr size_t size = _size;

  static constexpr inline Size() {
    return _size;
  }

  virtual reference At(const size_t _index)             = 0;
  virtual const_reference At(const size_t _index) const = 0;

  virtual ~StorageBase() = default;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_STORAGE_BASE_HPP

// SingularityLib/StorageBase.hpp