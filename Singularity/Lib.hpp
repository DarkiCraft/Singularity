#pragma once

#include "Types/Matrix.hpp"

#include "Core/Enums.hpp"
#include "Core/Dense.hpp"

#include "Op/Alg/Trp.hpp"
#include "Op/Arthm/Add.hpp"
#include "Op/Arthm/Mul.hpp"
#include "Op/Arthm/Neg.hpp"
#include "Op/Arthm/Sub.hpp"
#include "Op/Cmp/Eql.hpp"

#include "Expr/Evaluate.hpp"

#include "Traits/Size.hpp"
#include "Traits/Type.hpp"
#include "Traits/Core.hpp"
#include "Traits/Matrix.hpp"
#include "Traits/Expr.hpp"

#include <cstddef>

namespace Sglty {

template <typename _Tp,
          std::size_t _rows,
          std::size_t _cols,
          Core::Major _major = Core::Major::Row>
using DenseMatrix = Types::Matrix<Core::Dense<_Tp, _rows, _cols, _major>>;

}  // namespace Sglty

// Singularity/Lib.hpp
