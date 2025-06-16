# Singularity

(I CAN FINALLY WORK ON THIS AGAIN IN THE SUMMERS WOOHOOO!!!)

Singularity is a C++ header-only Linear Algebra library heavily inspired by [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) with a focus on compile-time metaprogramming. It’s built as a hobby project to learn and experiment with advanced C++ techniques.

## Goals:
- Provide linear algebra operations on matrices, vectors, and fields.
- Enable pluggable user-defined storage backends ("Cores") with full operation support.
- Serve as a learning ground for exploring template metaprogramming and library design.

## Non-Goals
- Competing with [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) or any industrial-grade linear algebra library.
- Providing runtime-optimized or dynamic-memory-backed performance.
- Offering full production-grade guarantees or widespread platform portability.

## Known limitations:
- Stack allocation has practical limits.
  - Matrices around 256×256 (with 4-byte types) are typically safe (~1MB).
  - Larger sizes may lead to stack overflows or crashes depending on your system and compiler settings.
  - If you need bigger matrices, allocate them on the heap with `new` — everything else works the same.

- No dynamic sizes or resizing.
  - All shapes are fixed at compile-time — no `resize()`, no runtime allocation logic.
  - This is by design: Singularity is built for static, type-safe, minimal-overhead linear algebra operations.

## Status:
Foundations for expressions done! Now need to reorganize internals, and remove bloat from `Sglty::` :)

Feedback and criticism are always welcome — I’m here to learn and make this better! <3
