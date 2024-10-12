#ifndef LEXER_HPP
#define LEXER_HPP

#include "Frontend/Token.hpp"

namespace MPIRectRule::Frontend {
    [[nodiscard]] constexpr bool isSpacing(char c) {
        return c == ' ' || c == '\t' || c == '\n';
    }

    [[nodiscard]] constexpr bool isNumeric(char c) {
        return c == '.' || (c >= '0' && c <= '9');
    }

    class Lexer {
    private:
        std::string m_source;
        std::size_t m_limit;
        std::size_t m_pos;

        [[nodiscard]] bool atEnd() const;

        Token lexSpacing();
        Token lexSingle(TokenTag tag);
        Token lexNumber();

    public:
        constexpr Lexer() : m_source {}, m_limit {0}, m_pos {0} {}
        Lexer(const std::string& source);

        Lexer(const Lexer& other);
        Lexer& operator=(const Lexer& other);

        const std::string& viewSource() const;

        [[nodiscard]] Token lexNext();
    };
}

#endif