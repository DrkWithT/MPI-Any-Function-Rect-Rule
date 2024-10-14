#ifndef PARSER_HPP
#define PARSER_HPP

#include <initializer_list>
#include <memory>
#include "Frontend/Token.hpp"
#include "Frontend/Lexer.hpp"
#include "Syntax/IAstNode.hpp"
#include "Frontend/Diagnostics.hpp"

namespace MPIRectRule::Frontend {    
    enum class TokenOption {
        previous,
        current
    };

    class Parser {
    private:
        using TokenTagList = std::initializer_list<TokenTag>;

        Lexer m_lexer;
        Token m_current;
        Token m_previous;

        const std::string& getLexicalSource() const;

        template <TokenOption Opt>
        [[nodiscard]] bool matchToken(const TokenTagList& tag_whitelist) const;

        template <>
        [[nodiscard]] bool matchToken<TokenOption::previous>(const TokenTagList& tag_whitelist) const {
            if (tag_whitelist.size() == 0) {
                return true;
            }

            for (const auto& tag : tag_whitelist) {
                if (m_previous.tag == tag) {
                    return true;
                }
            }

            return false;
        }

        template <>
        [[nodiscard]] bool matchToken<TokenOption::current>(const TokenTagList& tag_whitelist) const {
            if (tag_whitelist.size() == 0) {
                return true;
            }

            for (const auto& tag : tag_whitelist) {
                if (m_current.tag == tag) {
                    return true;
                }
            }

            return false;
        }

        template <TokenOption Opt>
        const Token& getTokenOf() const;

        template <>
        const Token& getTokenOf<TokenOption::previous>() const { return m_previous; }

        template <>
        const Token& getTokenOf<TokenOption::current>() const { return m_current; }

        [[nodiscard]] bool atEnd() const;

    public:
        explicit Parser(const std::string& source_str);

        [[nodiscard]] Token advanceToken();
        void consumeToken(const TokenTagList& tag_whitelist);

        std::unique_ptr<Syntax::IAstNode> parseLiteral();

        std::unique_ptr<Syntax::IAstNode> parseUnary();

        std::unique_ptr<Syntax::IAstNode> parsePower();

        std::unique_ptr<Syntax::IAstNode> parseFactor();

        std::unique_ptr<Syntax::IAstNode> parseTerm();

        std::unique_ptr<Syntax::IAstNode> parseAll();
    };
}

#endif