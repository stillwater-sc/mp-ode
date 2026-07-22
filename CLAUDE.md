# CLAUDE.md

Guidance for Claude Code (claude.ai/code) when working in this repository.

## Project Overview

mp-ode is the **integration layer** for mixed-precision ODE solvers.
It composes two header-only sister libraries:

- [MTL5](https://github.com/stillwater-sc/mtl5) — C++20 linear algebra.
- [Universal](https://github.com/stillwater-sc/universal) — parameterized number
  systems (`cfloat`, `posit`, ...).

**Architectural rule:** MTL5 is the general linear-algebra layer and MUST NOT
depend on Universal. All MTL5 + Universal coupling lives here in mp-ode.

## Build Commands

```bash
# Dependencies are pulled automatically via FetchContent.
cmake -B build -DCMAKE_BUILD_TYPE=Release -Wno-dev
cmake --build build -j
ctest --test-dir build --output-on-failure

# Use local sister checkouts instead of fetching from GitHub:
cmake -B build -DFETCHCONTENT_SOURCE_DIR_MTL5=../mtl5 \
               -DFETCHCONTENT_SOURCE_DIR_UNIVERSAL=../universal
```

## Architecture

- Header-only composition under `include/sw/mp_ode/`. Namespace: `sw::mp_ode`.
- CMake: INTERFACE library `sw::mp_ode` linking MTL5 + Universal. Options:
  `MPODE_BUILD_APPLICATIONS`, `MPODE_BUILD_TESTS`.
- `applications/` — demonstration programs (each its own CMakeLists).
- `tests/` — lightweight self-checking executables (no external framework);
  register with `mpode_add_test`.
- `docs/roadmap.md` — milestones and known integration work.

## Conventions

- C++20, header-only. Match the sister repos (mtl5, mp-spice) for style and
  CMake structure.
- Conventional Commits. Feature branches + PRs to `main`; CI must pass.
- Never commit build artifacts or downloaded data.
