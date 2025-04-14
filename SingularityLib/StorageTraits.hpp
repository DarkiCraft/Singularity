#ifndef SINGULARITYLIB_STORAGE_TRAITS_HPP
#define SINGULARITYLIB_STORAGE_TRAITS_HPP

#include <type_traits>

using size_t = unsigned long long;

namespace Sglty {

enum class StorageType { Dense, Sprse };
enum class StorageOrdr { RowMajor, ColMajor, Udefined };

template <StorageType _st_type, StorageOrdr _st_ordr>
struct StorageTraits {
  static constexpr StorageType storage_type = _st_type;
  static constexpr StorageOrdr storage_ordr = _st_ordr;
};

template <StorageType _st_type, StorageOrdr _st_ordr>
struct is_valid_storage_trait {
  static constexpr bool value =
      (_st_type == StorageType::Dense && (_st_ordr == StorageOrdr::RowMajor ||
                                          _st_ordr == StorageOrdr::ColMajor)) ||
      (_st_type == StorageType::Sprse && _st_ordr == StorageOrdr::Udefined);
};

template <StorageType _st_type, StorageOrdr _st_ordr>
constexpr bool is_valid_storage_trait_v =
    is_valid_storage_trait<_st_type, _st_ordr>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_STORAGE_TRAITS_HPP

// SingularityLib/StorageTraits.hpp