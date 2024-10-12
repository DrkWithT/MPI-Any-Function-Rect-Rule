/**
 * @file Token.cpp
 * @author DrkWithT
 * @brief Implements token helper functions.
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Frontend/Token.hpp"

namespace MPIRectRule::Frontend {
    static constexpr const char* placeholder_str = "??";

    std::string getLexeme(const Token& token, const std::string& source) {
        if (token.span == 0) {
            return placeholder_str;
        }

        return source.substr(token.begin, token.span);
    }
}