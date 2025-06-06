# SingularityLib

(I CAN FINALLY WORK ON THIS AGAIN IN THE SUMMERS WOOHOOO!!!)

SingularityLib is a C++ header-only Linear Algebra library heavily inspired by [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) with a focus on compile-time metaprogramming. It’s built as a hobby project to learn and experiment with advanced C++ techniques.

## Goals:
- Provide linear algebra operations on matrices, vectors, and fields
- Enable pluggable user-defined storage backends ("Cores") with full operation support
- Serve as a learning ground for exploring template metaprogramming and library design

## Non-Goals
- Competing with Eigen or any industrial-grade linear algebra library
- Providing runtime-optimized or dynamic-memory-backed performance
- Offering full production-grade guarantees or widespread platform portability

## Known limitations:
- All data is stack-allocated by design, for zero runtime overhead.
  - This imposes strict practical limits on object sizes (e.g., ~256×256 matrices are typically safe).
  - Larger sizes may result in stack overflow or crashes, depending on your system and compiler settings.
  - If you need massive matrices, this library probably isn’t the right fit — intentionally so.

## Status:
Working on the API :)

All feedback and criticism is welcome — I’m here to learn <3
