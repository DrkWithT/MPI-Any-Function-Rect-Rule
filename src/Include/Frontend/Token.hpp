#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace MPIRectRule::Frontend {
    enum class TokenTag {
        spacing,
        number,
        variable,
        op_power,
        op_times,
        op_slash,
        op_plus,
        op_minus,
        eos,
        bad
    };
    
    struct Token {
        std::size_t begin;
        std::size_t span;
        TokenTag tag;
    };

    [[nodiscard]] std::string getLexeme(const Token& token, const std::string& source);
}

#endif