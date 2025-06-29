#pragma once

namespace Sglty::Op::Cmp {

template <typename _lhs, typename _rhs>
constexpr bool IsEqual(const _lhs& _l, const _rhs& _r);

template <typename _lhs, typename _rhs>
constexpr bool IsNotEqual(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Op::Cmp

namespace Sglty::Types {

template <typename _lhs, typename _rhs>
constexpr bool operator==(const _lhs& _l, const _rhs& _r);

template <typename _lhs, typename _rhs>
constexpr bool operator!=(const _lhs& _l, const _rhs& _r);

}  // namespace Sglty::Types

#include "Impl/Eql.tpp"

// Singularity/Op/Cmp/Eql.hpp
