
# Singularity

Singularity is a C++ header-only Linear Algebra library heavily inspired by [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) with a focus on compile-time metaprogramming. It’s built as a hobby project to learn and experiment with advanced C++ techniques.

## Goals:
- Provide linear algebra operations.
- Enable pluggable user-defined storage backends ("Cores") with full operation support.
- Serve as a learning ground for exploring template metaprogramming and library design.

## Non-Goals
- Competing with [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) or any industrial-grade linear algebra library.
- Providing runtime-optimized or dynamic-memory-backed performance.
- Offering full production-grade guarantees or widespread platform portability.

## Example Usage:
```cpp
#include "Singularity/Lib.hpp"          // Core library
#include "Singularity/Convenience.hpp"  // Optional typedefs i.e. Sglty::DenseMat<...>
                                        // Uses Sglty::Core::Dense<...> internally

int main() {
  using Sglty::Core::Major;
  // using Sglty::Expr;

  constexpr Sglty::DenseMat<float, 2, 3>           a(1);
  constexpr Sglty::DenseMat<int, 3, 2, Major::Col> b(2);

  constexpr auto e /* Expr::Binary */ = a.Cast<int>() * b.Reorder<Major::Row>();

  constexpr Sglty::DenseMat<int, 2, 2> x     = e;            // constructs directly from e
  constexpr auto y /* decltype(y) inferred*/ = Evaluate(e);  // finds Expr::Evaluate() by ADL

  // element access via operator()(i, j)
  static_assert(x(0, 0) == 6);
  static_assert(x(0, 1) == 6);
  static_assert(x(1, 0) == 6);
  static_assert(x(1, 1) == 6);

  // same-core-typed matrix equality checks
  static_assert(x == y);
}
```

## Known limitations:
- Stack allocation has practical limits.
  - Matrices around 256×256 (with 4-byte types) are typically safe (~1MB).
  - Larger sizes may lead to stack overflows or crashes depending on your system and compiler settings.
  - If you need bigger matrices, allocate them on the heap with `new` — everything else works the same.

- No dynamic sizes or resizing.
  - All shapes are fixed at compile-time — no `resize()`, no runtime allocation logic.
  - This is by design: Singularity is built for static, type-safe, minimal-overhead linear algebra operations.

Feedback and criticism are always welcome — I’m here to learn and make this better! <3

## License:

This project is released under the [MIT License](LICENSE).
