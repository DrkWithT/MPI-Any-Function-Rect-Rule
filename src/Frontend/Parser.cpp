/**
 * @file Parser.cpp
 * @author DrkWithT
 * @brief Implements x expression parser.
 * @date 2024-10-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <utility>
#include <stdexcept>
#include <format>
#include <iostream>
#include "Frontend/Diagnostics.hpp"
#include "Frontend/Parser.hpp"
#include "Syntax/IAstNode.hpp"
#include "Syntax/IAstVisitor.hpp"
#include "Syntax/AstNodes.hpp"

namespace MPIRectRule::Frontend {
    const std::string& Parser::getLexicalSource() const { return m_lexer.viewSource(); }

    bool Parser::atEnd() const { return m_current.tag == TokenTag::eos; }

    Parser::Parser(const std::string& source_str)
    : m_lexer {source_str}, m_current {.tag = TokenTag::bad}, m_previous {.tag = TokenTag::bad} {}

    Token Parser::advanceToken() {
        Token temp;

        do {
            temp = m_lexer.lexNext();

            if (temp.tag == TokenTag::spacing) {
                continue;
            }

            break;
        } while (true);

        return temp;
    }

    void Parser::consumeToken(const TokenTagList& tag_whitelist) {
        if (matchToken<TokenOption::current>(tag_whitelist)) {
            m_previous = m_current;
            m_current = advanceToken();
            return;
        } else if (matchToken<TokenOption::current>({TokenTag::bad})) {
            throw std::runtime_error {formatDiagnosticText<ParseError::unknown_token>(m_lexer.viewSource(), m_current)};
        }

        throw std::runtime_error {formatDiagnosticText<ParseError::unexpected_token>(m_lexer.viewSource(), m_current)};
    }

    std::unique_ptr<Syntax::IAstNode> Parser::parseLiteral() {
        auto temp_token = getTokenOf<TokenOption::current>();
        auto lexical_tag = temp_token.tag;

        if (lexical_tag == TokenTag::number) {
            consumeToken({});
            return std::make_unique<Syntax::LiteralExpr>(temp_token);
        } else if (lexical_tag == TokenTag::variable) {
            consumeToken({});
            return std::make_unique<Syntax::LiteralExpr>(temp_token);
        }

        throw std::runtime_error {formatDiagnosticText<ParseError::unexpected_token>(m_lexer.viewSource(), temp_token)};
    }

    std::unique_ptr<Syntax::IAstNode> Parser::parseUnary() {
        auto temp_tag = getTokenOf<TokenOption::current>().tag;

        if (temp_tag == TokenTag::op_minus) {
            consumeToken({});
            return std::make_unique<Syntax::UnaryExpr>(parseLiteral(), Syntax::ExprOp::negate);
        }

        return parseLiteral();
    }

    std::unique_ptr<Syntax::IAstNode> Parser::parsePower() {
        auto temp_unary = parseUnary();
        auto current_tag = getTokenOf<TokenOption::current>().tag;

        if (current_tag == TokenTag::op_power) {
            consumeToken({});
            auto temp_exponent = parseLiteral();
            return std::make_unique<Syntax::BinaryExpr>(std::move(temp_unary), std::move(temp_exponent), Syntax::ExprOp::pow);
        }

        return temp_unary;
    }

    std::unique_ptr<Syntax::IAstNode> Parser::parseFactor() {
        auto lhs = parsePower();

        while (!atEnd()) {
            auto temp_tag = getTokenOf<TokenOption::current>().tag;

            if (temp_tag != TokenTag::op_times && temp_tag != TokenTag::op_slash) {
                break;
            }

            auto op = (temp_tag == TokenTag::op_times)
                ? Syntax::ExprOp::mul
                : Syntax::ExprOp::div;

            consumeToken({});

            auto rhs = parsePower();

            lhs = std::make_unique<Syntax::BinaryExpr>(std::move(lhs), std::move(rhs), op);
        }

        return lhs;
    }

    std::unique_ptr<Syntax::IAstNode> Parser::parseTerm() {
        auto lhs = parseFactor();

        while (!atEnd()) {
            auto temp_tag = getTokenOf<TokenOption::current>().tag;

            if (temp_tag != TokenTag::op_plus && temp_tag != TokenTag::op_minus) {
                break;
            }

            auto op = (temp_tag == TokenTag::op_plus)
                ? Syntax::ExprOp::add
                : Syntax::ExprOp::sub;
            
            consumeToken({});

            auto rhs = parseFactor();

            lhs = std::make_unique<Syntax::BinaryExpr>(std::move(lhs), std::move(rhs), op);
        }

        return lhs;
    }

    std::unique_ptr<Syntax::IAstNode> Parser::parseAll() {
        try {
            consumeToken({});
            return parseTerm();
        } catch (const std::runtime_error& parse_err) {
            std::cerr << parse_err.what();
        }

        return nullptr;
    }
}
