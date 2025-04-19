#ifndef SINGULARITYLIB_MATRIX_STORAGE_TRAITS_HPP
#define SINGULARITYLIB_MATRIX_STORAGE_TRAITS_HPP

#include <type_traits>

using size_t = unsigned long long;

namespace Sglty {

enum class StorageType { Static, Dynamc };
enum class StorageMode { Dense, Sprse };
enum class StorageOrdr { RowMajor, ColMajor, Udefined };

template <StorageType _st_type, StorageMode _st_mode, StorageOrdr _st_ordr>
struct StorageTraits {
  static constexpr StorageType storage_type = _st_type;
  static constexpr StorageMode storage_mode = _st_mode;
  static constexpr StorageOrdr storage_ordr = _st_ordr;
};

template <StorageType _st_type, StorageMode _st_mode, StorageOrdr _st_ordr>
struct is_valid_storage_traits
    : std::bool_constant<(_st_mode == StorageMode::Dense &&
                              (_st_ordr == StorageOrdr::RowMajor ||
                               _st_ordr == StorageOrdr::ColMajor) ||
                          _st_mode == StorageMode::Sprse)> {};

template <StorageType _st_type, StorageMode _st_mode, StorageOrdr _st_ordr>
constexpr bool is_valid_storage_traits_v =
    is_valid_storage_traits<_st_type, _st_mode, _st_ordr>::value;

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_STORAGE_TRAITS_HPP

// SingularityLib/Matrix/StorageTraits.hpp