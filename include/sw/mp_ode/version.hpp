#pragma once
// mp-ode -- mixed-precision ODE solvers (MTL5 + Universal)
//
// Header-only composition layer. As shared utilities emerge (time steppers,
// mixed-precision integrator harnesses, adaptive step-size controllers), they
// live under sw::mp_ode. For now this header carries only version metadata.

namespace sw::mp_ode {

inline constexpr int version_major = 0;
inline constexpr int version_minor = 1;
inline constexpr int version_patch = 0;

} // namespace sw::mp_ode
