#ifndef SINGULARITYLIB_MATRIX_HPP
#define SINGULARITYLIB_MATRIX_HPP

#include <type_traits>

#include "Matrix/StorageCore.hpp"

using size_t = unsigned long long;

namespace Sglty {

template <typename _storage_impl>
class Matrix {
  static_assert(is_valid_storage_implementation_v<_storage_impl>,
                "Invalid Storage Implementation");

  static_assert(is_valid_storage_traits_v<_storage_impl::StorageType(),
                                          _storage_impl::StorageMode(),
                                          _storage_impl::StorageOrdr()>,
                "Invalid StorageTrait<> combination");

 public:
  template <typename _dummy_t = _storage_impl,
            typename          = std::enable_if_t<_dummy_t::StorageType() ==
                                                 StorageType::Static>>
  Matrix() {}

  template <typename _dummy_t = _storage_impl,
            typename          = std::enable_if_t<_dummy_t::StorageType() ==
                                                 StorageType::Dynamc>>
  Matrix(const size_t _rows, const size_t _cols) {}

 private:
  _storage_impl _m_data;
};

}  // namespace Sglty

#endif  // SINGULARITYLIB_MATRIX_HPP

// SingularityLib/Matrix.hpp