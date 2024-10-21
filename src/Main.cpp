/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief Implements MPI C++ program that calculates Rectangle Rule approximation of user entered variable function types, e.g `2x^2 + x - 1`.
 * @note The rectangle sum will be done by left-hand chunks.
 * @note It would be more performant to leave the parsing and compiling on the root process, but implementing the parallel program structure would be overkill and even easier to be buggy.
 * @version 0.1.0
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <mpi.h>
#include <algorithm>
#include <memory>
#include <string>
#include <iostream>

#include "Models/FunctionParts.hpp"
#include "Models/XFunction.hpp"
#include "Frontend/Parser.hpp"
#include "Syntax/IAstNode.hpp"
#include "Backend/FuncEmitter.hpp"
#include "MpiWraps/Wrappers.hpp"

using namespace MPIRectRule;

static constexpr std::size_t source_length_limit = 50; // length in chars of x-function expr.
static constexpr std::size_t source_buffer_size = source_length_limit + 1; // includes NUL char!

void getFunctionText(std::unique_ptr<char[]>& source_buffer, MpiWraps::MPIContext& ctx) {
    if (ctx.getProcessRank() == ctx.getMasterRank()) {
        std::string temp_input;

        do {
            std::cout << "Enter function (at most 50 letters long):\n";
            std::getline(std::cin, temp_input);
        } while (temp_input.size() == 0 || temp_input.size() > 50);

        const char* temp_src_ptr = temp_input.c_str();
        std::copy(temp_src_ptr, temp_src_ptr + temp_input.size(), source_buffer.get());
    }

    MPI_Bcast(source_buffer.get(), source_length_limit, MPI_CHAR, ctx.getMasterRank(), ctx.getCommunicator());
}

void getRectRuleParams(double *a_ptr, double *b_ptr, int *slices_ptr, MpiWraps::MPIContext& ctx) {
    if (ctx.getProcessRank() == ctx.getMasterRank()) {
        double temp_a, temp_b;
        double temp_slices_n;

        std::cout << "Enter lowest bound of rectangle sum:\n";
        std::cin >> temp_a;

        std::cout << "Enter highest bound of rectangle sum:\n";
        std::cin >> temp_b;

        std::cout << "Enter count of rectangles:\n";
        std::cin >> temp_slices_n;

        *a_ptr = temp_a;
        *b_ptr = temp_b;
        *slices_ptr = temp_slices_n;
    }

    MPI_Bcast(a_ptr, 1, MPI_DOUBLE, ctx.getMasterRank(), ctx.getCommunicator());
    MPI_Bcast(b_ptr, 1, MPI_DOUBLE, ctx.getMasterRank(), ctx.getCommunicator());
    MPI_Bcast(slices_ptr, 1, MPI_DOUBLE, ctx.getMasterRank(), ctx.getCommunicator());
}

Models::XFunction compileFromSource(const std::string& source) {
    Frontend::Parser parser {source};
    Backend::FuncEmitter emitter {source};

    auto ast = parser.parseAll();

    return emitter.generateFunction(ast);
}

[[nodiscard]] double doParallelRectSum(double local_a, double local_n, double local_dx, const Models::XFunction& fn, MpiWraps::MPIContext& ctx) {
    double final_estimate = 0.0;

    double temp_estimate = 0.0;
    double temp_x = 0.0;

    for (int i = 0; i < local_n; i++) {
        temp_x = local_a + local_dx * i;
        temp_estimate += Models::evaluateFunction(fn, temp_x) * local_dx;
    }

    MPI_Reduce(&temp_estimate, &final_estimate, 1, MPI_DOUBLE, MPI_SUM, ctx.getMasterRank(), ctx.getCommunicator());

    return final_estimate;
}

int main() {
    /// Create MPI context.
    MpiWraps::MPIContext ctx;

    double a = 0.0, b = 0.0;
    double local_a = 0.0, local_dx = 0.0;
    double total_integral = 0.0;
    int n = 0, local_n = 0;

    std::unique_ptr<char[]> source_buffer = std::make_unique<char[]>(source_buffer_size);
    std::fill(source_buffer.get(), source_buffer.get() + source_buffer_size, '\0');

    std::string source_str;

    /// Get and broadcast source of x-function...
    getFunctionText(source_buffer, ctx);

    /// Get input of rectangle rule bounds: a, b relative to x-axis, slice count
    getRectRuleParams(&a, &b, &n, ctx);

    /// Deduce local x-intervals & local bounds for each process.
    local_dx = (b - a) / n;
    local_n = n / ctx.getProcessCount();
    local_a = a + ctx.getProcessRank() * local_n * local_dx;

    /// Compile simple x-function from local source copy.
    source_str = source_buffer.get();
    auto fn = compileFromSource(source_str);

    /// If the function parses well, the AST exists. Thus the AST results in a non-empty, valid sequence of steps.
    if (fn.steps.size() == 0) {
        if (ctx.getProcessRank() == ctx.getMasterRank()) {
            std::cerr << "Error: entered function was invalid. Please check messages above.\n";
        }

        return 1;
    }

    /// Evaluate parts of the rectangle rule sum in parallel!
    total_integral = doParallelRectSum(local_a, local_n, local_dx, fn, ctx);

    if (ctx.getProcessRank() == ctx.getMasterRank()) {
        std::cout << "integral ~= " << total_integral << '\n';
    }
}