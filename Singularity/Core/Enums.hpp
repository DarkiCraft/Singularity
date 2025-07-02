#pragma once

namespace Sglty::Core {

/**
 * @brief Enum representing core storage type.
 *
 * Identifies the kind of backing storage a matrix uses.
 * Used primarily in `core_traits` and compile-time dispatch.
 */
enum class Type {
  /// Standard dense storage (e.g. std::array, linear buffers).
  Dense,

  /// Sparse or non-contiguous representation (e.g. compressed formats).
  Sparse
};

/**
 * @brief Enum representing memory layout order.
 *
 * Describes whether matrix elements are laid out in row-major or column-major
 * order. This impacts indexing and traversal logic.
 */
enum class Major {
  /// Row-major layout (C-style).
  Row,

  /// Column-major layout (Fortran-style).
  Col,

  /// Used when layout is unspecified or irrelevant.
  Undefined
};

}  // namespace Sglty::Core

// Singularity/Core/Enums.hpp
