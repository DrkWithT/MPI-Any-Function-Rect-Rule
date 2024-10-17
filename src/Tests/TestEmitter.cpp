/**
 * @file TestEmitter.cpp
 * @author DrkWithT
 * @brief Implements test program for FuncEmitter.
 * @version 0.1.0
 * @date 2024-10-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <memory>
#include <string>
#include <vector>
#include <format>
#include <iostream>

#include "Frontend/Parser.hpp"
#include "Syntax/IAstNode.hpp"
#include "Models/XFunction.hpp"
#include "Backend/FuncEmitter.hpp"

using MyParser = MPIRectRule::Frontend::Parser;
using AstNode = MPIRectRule::Syntax::IAstNode;
using MyFunc = MPIRectRule::Models::XFunction;
using MyEmitter = MPIRectRule::Backend::FuncEmitter;
using MPIRectRule::Models::evaluateFunction;

static constexpr const char* test_source_1 = "x^2 + 5 * x + 6";
static constexpr double test_x_1 = -2.5;
static constexpr double test_y_1 = -0.25;

static constexpr const char* test_source_2 = "1 / x^2";
static constexpr double test_x_2 = 0.5;
static constexpr double test_y_2 = 4.0;

int main() {
    std::string src_str_1 {test_source_1};
    MyParser parser_1 {src_str_1};
    auto ast_1 = parser_1.parseAll();

    MyEmitter emitter_1 {src_str_1};
    auto poly_fn = emitter_1.generateFunction(ast_1);

    if (evaluateFunction(poly_fn, test_x_1) != test_y_1) {
        std::cerr << std::format("Unexpected result of x = {}, f(x) = {}\n", test_x_1, src_str_1);
        return 1;
    }

    std::string src_str_2 {test_source_2};
    MyParser parser_2 {src_str_2};
    auto ast_2 = parser_2.parseAll();

    MyEmitter emitter_2 {src_str_2};
    auto rational_fn = emitter_2.generateFunction(ast_2);

    if (evaluateFunction(rational_fn, test_x_2) != test_y_2) {
        std::cerr << std::format("Unexpected result of x = {}, f(x) = {}\n", test_x_2, src_str_2);
        return 1;
    }
}
