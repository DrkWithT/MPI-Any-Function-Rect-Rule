#ifndef X_FUNCTION_HPP
#define X_FUNCTION_HPP

#include <vector>
#include "Models/FunctionParts.hpp"

namespace MPIRectRule::Models {
    struct XFunction {
        std::vector<ComputeStep> steps; // compiled transformations on a given value of x
    };

    [[nodiscard]] double evaluateFunction(const XFunction& func, double x);
}

#endif