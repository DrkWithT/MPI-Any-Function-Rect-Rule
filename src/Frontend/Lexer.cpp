/**
 * @file Lexer.cpp
 * @author DrkWithT
 * @brief Implements lexer for simple x-functions.
 * @date 2024-10-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Frontend/Lexer.hpp"
#include "Frontend/Token.hpp"

namespace MPIRectRule::Frontend {
    bool Lexer::atEnd() const {
        return m_pos >= m_limit;
    }

    Token Lexer::lexSpacing() {
        std::size_t tbegin = m_pos;
        std::size_t tspan = 0;

        while (!atEnd()) {
            if (!isSpacing(m_source[m_pos])) {
                break;
            }

            tspan++;
            m_pos++;
        }

        return {tbegin, tspan, TokenTag::spacing};
    }

    Token Lexer::lexSingle(TokenTag tag) {
        std::size_t tbegin = m_pos++;

        return {tbegin, 1, tag};
    }

    Token Lexer::lexNumber() {
        std::size_t tbegin = m_pos;
        std::size_t tspan = 0;
        int dots = 0;

        while (!atEnd()) {
            char s = m_source[m_pos];

            if (!isNumeric(s)) {
                break;
            }

            if (s == '.') {
                dots++;
            }

            tspan++;
            m_pos++;
        }

        if (dots < 2) {
            return {.begin = tbegin, .span = tspan, .tag = TokenTag::number};
        }

        return {tbegin, tspan, TokenTag::bad};
    }

    Lexer::Lexer(const std::string& source)
    : m_source {source}, m_limit {source.size()}, m_pos {0} {}

    Lexer::Lexer(const Lexer& other) {
        if (&other == this) {
            return;
        }

        m_source = other.m_source;
        m_limit = other.m_limit;
        m_pos = other.m_pos;
    }

    Lexer& Lexer::operator=(const Lexer& other) {
        if (&other == this) {
            return *this;
        }

        m_source = other.m_source;
        m_limit = other.m_limit;
        m_pos = other.m_pos;

        return *this;
    }

    const std::string& Lexer::viewSource() const { return m_source; }

    Token Lexer::lexNext() {
        if (atEnd()) {
            return {m_pos, 1, TokenTag::eos};
        }

        char temp = m_source[m_pos];

        switch (temp) {
            case 'x':
                return lexSingle(TokenTag::variable);
            case '+':
                return lexSingle(TokenTag::op_plus);
            case '-':
                return lexSingle(TokenTag::op_minus);
            case '*':
                return lexSingle(TokenTag::op_times);
            case '/':
                return lexSingle(TokenTag::op_slash);
            case '^':
                return lexSingle(TokenTag::op_power);
            default:
                break;
        }

        if (isSpacing(temp)) {
            return lexSpacing();
        } else if (isNumeric(temp)) {
            return lexNumber();
        }

        return {m_pos++, 1, TokenTag::bad};
    }
}