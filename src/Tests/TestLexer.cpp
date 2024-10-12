/**
 * @file TestLexer.cpp
 * @author DrkWithT
 * @brief Implements Lexer tests.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <initializer_list>
#include <format>
#include <iostream>
#include "Frontend/Token.hpp"
#include "Frontend/Lexer.hpp"

using MyLexer = MPIRectRule::Frontend::Lexer;
using MyToken = MPIRectRule::Frontend::Token;
using MyTokenTag = MPIRectRule::Frontend::TokenTag;
using TokenTagList = std::initializer_list<MyTokenTag>;

static constexpr const char* test_source_1 = "x^2  + 2*x -  3";
static constexpr const char* test_source_2 = " a +  5.25.0";

[[nodiscard]] bool testLexingRun(const char* src_literal, const TokenTagList& token_list) {
    MyLexer lexer {src_literal};
    auto cursor = token_list.begin();
    auto ending = token_list.end();

    for (; cursor != ending; cursor++) {
        auto temp_tag = lexer.lexNext().tag;

        if (temp_tag != *cursor) {
            return false;
        }
    }

    return true;
}

int main() {
    TokenTagList test_tags_1 {
        MyTokenTag::variable,
        MyTokenTag::op_power,
        MyTokenTag::number,
        MyTokenTag::spacing,
        MyTokenTag::op_plus,
        MyTokenTag::spacing,
        MyTokenTag::number,
        MyTokenTag::op_times,
        MyTokenTag::variable,
        MyTokenTag::spacing,
        MyTokenTag::op_minus,
        MyTokenTag::spacing,
        MyTokenTag::number,
        MyTokenTag::eos
    };

    if (!testLexingRun(test_source_1, test_tags_1)) {
        std::cerr << std::format("Unexpected lexing for source: \"{}\"\n", test_source_1);
        return 1;
    }

    TokenTagList test_tags_2 {
        MyTokenTag::spacing,
        MyTokenTag::bad,
        MyTokenTag::spacing,
        MyTokenTag::op_plus,
        MyTokenTag::spacing,
        MyTokenTag::bad,
        MyTokenTag::eos
    };

    if (!testLexingRun(test_source_2, test_tags_2)) {
        std::cerr << std::format("Unexpected lexing for source: \"{}\"\n", test_source_2);
        return 1;
    }
}