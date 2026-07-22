// euler_precision: forward Euler on the linear decay ODE y' = -y, y(0) = 1,
// integrated over [0, 1], compared across number types. Demonstrates the
// MTL5 + Universal composition pattern: the integrator is value-type generic,
// the number system is a template parameter.
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>

#include <mtl/vec/dense_vector.hpp>

#include <universal/number/posit/posit.hpp>
#include <universal/number/cfloat/cfloat.hpp>

namespace {

// One forward-Euler integration of y' = -y over [0, 1] with the given step
// count; returns |y(1) - exp(-1)| evaluated in double.
template <typename T>
double euler_error(std::size_t steps) {
    T y = T(1);
    const T h = T(1) / T(static_cast<int>(steps));
    for (std::size_t s = 0; s < steps; ++s)
        y = y - h * y;
    return std::abs(static_cast<double>(y) - std::exp(-1.0));
}

template <typename T>
void report(const std::string& name, std::size_t steps) {
    std::cout << "  " << std::left << std::setw(16) << name
              << std::scientific << std::setprecision(3)
              << euler_error<T>(steps) << '\n';
}

} // namespace

int main(int argc, char* argv[]) {
    std::size_t steps = 64;
    if (argc > 1) steps = static_cast<std::size_t>(std::stoul(argv[1]));

    std::cout << "forward Euler on y' = -y over [0,1], " << steps << " steps\n";
    std::cout << "  type            |y(1) - exp(-1)|\n";
    std::cout << "  --------------------------------\n";
    report<double>("double", steps);
    report<float>("float", steps);
    report<sw::universal::cfloat<16, 5>>("cfloat<16,5>", steps);
    report<sw::universal::posit<16, 2>>("posit<16,2>", steps);
    return 0;
}
