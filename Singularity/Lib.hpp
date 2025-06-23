#pragma once

// Core interfaces (if you want to expose them — otherwise skip)
#include "Core/Checks.hpp"
#include "Core/Dense.hpp"
#include "Core/Enums.hpp"

// Expression machinery
#include "Expr/Base.hpp"
#include "Expr/Evaluate.hpp"

// Traits — you may or may not want to expose these at top level
#include "Traits/Core.hpp"
#include "Traits/Expr.hpp"
#include "Traits/Matrix.hpp"
#include "Traits/Size.hpp"
#include "Traits/Type.hpp"

// Types (main user-facing types)
#include "Types/Matrix.hpp"
// #include "Types/Vector.hpp" // future

// Ops (grouped, or you could split if users want finer control)
#include "Ops/Alg/Trp.hpp"
#include "Ops/Arthm/Add.hpp"
#include "Ops/Arthm/Mul.hpp"
#include "Ops/Arthm/Sub.hpp"