#pragma once

#include "../Dense.hpp"

#include <cstddef>
#include <utility>

namespace Sglty::Core {

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr Dense<_Tp, _rows, _cols, _core_major>::Dense() = default;

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr Dense<_Tp, _rows, _cols, _core_major>::Dense(value_type val)
    : _m_data() {
  for (size_type i = 0; i < _m_data.size(); i++) {
    _m_data[i] = val;
  }
}

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr typename Dense<_Tp, _rows, _cols, _core_major>::reference
Dense<_Tp, _rows, _cols, _core_major>::At(const size_type _row,
                                          const size_type _col) {
  return const_cast<reference>(std::as_const(*this).At(_row, _col));
}

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr typename Dense<_Tp, _rows, _cols, _core_major>::const_reference
Dense<_Tp, _rows, _cols, _core_major>::At(const size_type _row,
                                          const size_type _col) const {
  return _m_Get(_row, _col);
}

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr typename Dense<_Tp, _rows, _cols, _core_major>::pointer
Dense<_Tp, _rows, _cols, _core_major>::Data() {
  return const_cast<pointer>(std::as_const(*this).Data());
}

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr typename Dense<_Tp, _rows, _cols, _core_major>::const_pointer
Dense<_Tp, _rows, _cols, _core_major>::Data() const {
  return _m_data.data();
}

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr inline typename Dense<_Tp, _rows, _cols, _core_major>::reference
Dense<_Tp, _rows, _cols, _core_major>::_m_Get(const size_type _row,
                                              const size_type _col) {
  return const_cast<reference>(std::as_const(*this)._m_Get(_row, _col));
}

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
constexpr inline typename Dense<_Tp, _rows, _cols, _core_major>::const_reference
Dense<_Tp, _rows, _cols, _core_major>::_m_Get(const size_type _row,
                                              const size_type _col) const {
  if (core_traits::core_major == Core::Major::Row) {
    return _m_data[_row * _cols + _col];
  } else {
    return _m_data[_col * _rows + _row];
  }
}

}  // namespace Sglty::Core

// Singularity/Core/Impl/Dense.tpp
