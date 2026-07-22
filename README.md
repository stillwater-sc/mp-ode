# mp-ode

[![CMake](https://github.com/stillwater-sc/mp-ode/actions/workflows/cmake.yml/badge.svg)](https://github.com/stillwater-sc/mp-ode/actions/workflows/cmake.yml)

**Mixed-precision Ordinary Differential Equation solvers.** mp-ode composes two
header-only libraries — [MTL5](https://github.com/stillwater-sc/mtl5) for linear
algebra and [Universal](https://github.com/stillwater-sc/universal) for
parameterized number systems — to explore ODE integrators under custom
arithmetic (half precision, posits, ...).

MTL5 deliberately has **no dependency on Universal**: it is the general
linear-algebra layer. mp-ode is the integration layer where MTL5's algorithms
meet Universal's number types.

## Build

```bash
# Dependencies (MTL5 + Universal) are pulled automatically via FetchContent.
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

# Run the smoke test
ctest --test-dir build --output-on-failure

# Run the forward-Euler precision demo (optional arg: step count)
./build/applications/euler_precision/euler_precision
```

Using local checkouts instead of fetching from GitHub:

```bash
cmake -B build \
  -DFETCHCONTENT_SOURCE_DIR_MTL5=../mtl5 \
  -DFETCHCONTENT_SOURCE_DIR_UNIVERSAL=../universal
```

## Layout

```
applications/euler_precision/   # forward Euler accuracy across precisions
include/sw/mp_ode/              # shared composition-layer headers
tests/                          # smoke tests
docs/roadmap.md                 # milestones and known integration work
```

## License

MIT — see [LICENSE](LICENSE).
