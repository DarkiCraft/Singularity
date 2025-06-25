#pragma once

#include <cstddef>
#include <array>

#include "Enums.hpp"
#include "../Traits/Type.hpp"
#include "../Traits/Size.hpp"
#include "../Traits/Core.hpp"

namespace Sglty::Core {

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _core_major>
class Dense {
 public:
  using type_traits = Traits::Type<_Tp>;

  using size_type       = typename type_traits::size_type;
  using value_type      = typename type_traits::value_type;
  using difference_type = typename type_traits::difference_type;
  using reference       = typename type_traits::reference;
  using const_reference = typename type_traits::const_reference;
  using pointer         = typename type_traits::pointer;
  using const_pointer   = typename type_traits::const_pointer;

  using size_traits = Traits::Size<_rows, _cols, size_type>;

  using core_traits = Traits::Core<Core::Mode::Dense, _core_major>;

  template <size_type _rebind_rows, size_type _rebind_cols>
  using core_rebind =
      Dense<_Tp, _rebind_rows, _rebind_cols, core_traits::core_major>;

  using core_base = Dense<_Tp, 0, 0, core_traits::core_major>;

  constexpr Dense();
  constexpr Dense(value_type val);

  constexpr reference At(const size_type _row, const size_type _col);
  constexpr const_reference At(const size_type _row,
                               const size_type _col) const;

  constexpr pointer Data();
  constexpr const_pointer Data() const;

 private:
  std::array<_Tp, _rows * _cols> _m_data;

  constexpr inline reference _m_Get(const size_type _row, const size_type _col);
  constexpr inline const_reference _m_Get(const size_type _row,
                                          const size_type _col) const;
};

}  // namespace Sglty::Core

#include "Impl/Dense.tpp"

// Singularity/Core/Dense.hpp
