# mp-ode roadmap

## Milestone 0: composition layer bootstrapped (done)

- CMake scaffold replicated from [mp-spice](https://github.com/stillwater-sc/mp-spice):
  INTERFACE library `sw::mp_ode`, find_package → FetchContent fallback for
  MTL5 + Universal, config-package install, CI matrix (MSVC/GCC/Clang/AppleClang).
- Smoke test: forward Euler on a linear decay system in `double`, `float`,
  `cfloat<16,5>`, and `posit<16,2>`.
- Demo application: `euler_precision` accuracy table across number types.

## Milestone 1: value-type-generic integrator library

- Explicit steppers (Euler, RK4, adaptive RK45) as templates over the number
  type, under `include/sw/mp_ode/`.
- Implicit steppers (backward Euler, trapezoidal/BDF) driving MTL5 linear
  solvers — the point where mixed-precision linear algebra enters.

## Milestone 2: mixed-precision studies

- Step-size vs precision trade-off: when does rounding error dominate
  discretization error per number type?
- Mixed schemes: low-precision stage evaluations with high-precision
  accumulation of the solution state.
- Stiff problems: precision requirements of the inner Newton/linear solves.
