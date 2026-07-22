// mp-ode smoke test: verify the MTL5 + Universal composition builds and that a
// forward-Euler step loop integrates a linear decay system in each number type.
// Returns non-zero on failure (no external test framework, matching the repo's
// lightweight style).
#include <cmath>
#include <cstddef>
#include <iostream>

#include <mtl/vec/dense_vector.hpp>

// Universal number types: the integrator must step in these through the MTL5 +
// Universal composition.
#include <universal/number/posit/posit.hpp>
#include <universal/number/cfloat/cfloat.hpp>

namespace {

// Integrate y' = -lambda .* y, y(0) = 1, over [0, 1] with forward Euler and
// compare against the exact solution exp(-lambda) in double.
template <typename T>
bool integrate_ok(double tol) {
    constexpr std::size_t steps = 64;
    const double lambda[2] = {1.0, 2.0};

    mtl::vec::dense_vector<T> y(2, T(1));
    const T h = T(1) / T(static_cast<int>(steps));
    for (std::size_t s = 0; s < steps; ++s) {
        for (int i = 0; i < 2; ++i)
            y(i) = y(i) - h * T(lambda[i]) * y(i);
    }

    // error ||y - exp(-lambda)||_inf in double
    double err = 0.0;
    for (int i = 0; i < 2; ++i)
        err = std::max(err, std::abs(static_cast<double>(y(i)) - std::exp(-lambda[i])));
    return err < tol;
}

} // namespace

int main() {
    int failures = 0;

    // Discretization error of forward Euler at h = 1/64 dominates here (~4e-3).
    if (!integrate_ok<double>(1e-2)) { std::cerr << "double Euler integration failed\n"; ++failures; }
    if (!integrate_ok<float>(1e-2))  { std::cerr << "float Euler integration failed\n";  ++failures; }

    // Low precision: rounding error accumulates on top of discretization error.
    if (!integrate_ok<sw::universal::cfloat<16, 5>>(5e-2)) {
        std::cerr << "cfloat<16,5> Euler integration failed\n"; ++failures;
    }
    if (!integrate_ok<sw::universal::posit<16, 2>>(5e-2)) {
        std::cerr << "posit<16,2> Euler integration failed\n"; ++failures;
    }

    if (failures == 0) std::cout << "mp-ode smoke test passed\n";
    return failures == 0 ? 0 : 1;
}
