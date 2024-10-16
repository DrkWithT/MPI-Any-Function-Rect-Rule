/**
 * @file XFunction.cpp
 * @author DrkWithT
 * @brief Implements utilities for x-function models.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <cmath>
#include <stack>
#include "Models/FunctionParts.hpp"
#include "Models/XFunction.hpp"

namespace MPIRectRule::Models {
    double evaluateFunction(const XFunction& func, double x) {
        const std::vector<ComputeStep>& func_steps = func.steps;
        std::stack<double> temps;
        double arg_0 = 0, arg_1 = 0;

        for (const auto& step : func_steps) {
            switch (step.op) {
                case load_x:
                    temps.push(x);
                    break;
                case push_const:
                    temps.push(step.constant);
                    break;
                case add:
                    arg_0 = temps.top();
                    temps.pop();
                    arg_1 = temps.top();
                    temps.pop();

                    temps.push(arg_0 + arg_1);
                    break;
                case sub:
                    arg_0 = temps.top();
                    temps.pop();
                    arg_1 = temps.top();
                    temps.pop();

                    temps.push(arg_1 - arg_0);
                    break;
                case mul:
                    arg_0 = temps.top();
                    temps.pop();
                    arg_1 = temps.top();
                    temps.pop();

                    temps.push(arg_0 * arg_1);
                    break;
                case div:
                    arg_0 = temps.top();
                    temps.pop();
                    arg_1 = temps.top();
                    temps.pop();

                    temps.push(arg_1 / arg_0);
                case pow:
                    arg_0 = temps.top();
                    temps.pop();
                    arg_1 = temps.top();
                    temps.pop();

                    temps.push(std::pow(arg_1, arg_0));
                case ComputeOp::nop:
                default:
                    break;
            }
        }

        return temps.top();
    }
}