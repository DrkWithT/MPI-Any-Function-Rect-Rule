/**
 * @file TestParser.cpp
 * @author DrkWithT
 * @brief Implements simple tests for parser.
 * @version 0.1.0
 * @date 2024-10-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <format>
// #include <string>
#include "Frontend/Parser.hpp"
#include "Syntax/IAstNode.hpp"

using MyParser = MPIRectRule::Frontend::Parser;
using MyAstNode = MPIRectRule::Syntax::IAstNode;

static constexpr const char* test_source_1 = "x^2 + 5 * x - 6"; // must parse fine!
static constexpr const char* test_source_2 = "42 - a"; // must give parse error!

int main() {
    MyParser parser_1 {test_source_1};
    auto ast_ptr_1 = parser_1.parseAll();

    if (!ast_ptr_1) {
        std::cerr << std::format("Unexpected parse failure for source \"{}\"\n", test_source_1);
        return 1;
    }

    MyParser parser_2 {test_source_2};
    auto ast_ptr_2 = parser_2.parseAll();

    if (ast_ptr_2 != nullptr) {
        std::cerr << std::format("Unexpected parse success for source \"{}\"\n", test_source_2);
        return 1;
    }
}
