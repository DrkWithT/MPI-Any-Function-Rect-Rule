/**
 * @file FuncEmitter.cpp
 * @author DrkWithT
 * @brief Implements AST to XFunction converter, so this is pretty much a compiler.
 * @version 0.1.0
 * @date 2024-10-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <utility>
#include "Frontend/Token.hpp"
#include "Backend/FuncEmitter.hpp"
#include "Models/FunctionParts.hpp"

namespace MPIRectRule::Backend {
    using Frontend::TokenTag;
    using Syntax::ExprOp;
    using Models::ComputeOp;

    FuncEmitter::FuncEmitter(const std::string& source)
    : m_compiled_steps {}, m_source {source} {}

    void FuncEmitter::visitLiteralExpr(Syntax::LiteralExpr& expr) {
        auto expr_token = expr.getToken();
        auto expr_token_tag = expr_token.tag;

        if (expr_token_tag == TokenTag::number) {
            auto num = std::stod(Frontend::getLexeme(expr_token, m_source));

            m_compiled_steps.push_back({num, ComputeOp::push_const});
        } else if (expr_token_tag == TokenTag::variable) {
            m_compiled_steps.push_back({0, ComputeOp::load_x});
        } else {
            m_compiled_steps.push_back({0, ComputeOp::nop});
        }
    }

    void FuncEmitter::visitUnaryExpr(Syntax::UnaryExpr& expr) {
        auto expr_op = expr.getOp();

        if (expr_op == ExprOp::negate) {
            m_compiled_steps.push_back({0, ComputeOp::push_const});
            expr.getInnerPtr()->acceptVisitor(*this);
            m_compiled_steps.push_back({0, ComputeOp::sub});
        } else {
            m_compiled_steps.push_back({0, ComputeOp::nop});
        }
    }

    void FuncEmitter::visitBinaryExpr(Syntax::BinaryExpr& expr) {
        auto expr_op = expr.getOp();

        if (expr_op == ExprOp::add) {
            expr.getLeftPtr()->acceptVisitor(*this);
            expr.getRightPtr()->acceptVisitor(*this);
            m_compiled_steps.push_back({0, ComputeOp::add});
        } else if (expr_op == ExprOp::sub) {
            expr.getLeftPtr()->acceptVisitor(*this);
            expr.getRightPtr()->acceptVisitor(*this);
            m_compiled_steps.push_back({0, ComputeOp::sub});
        } else if (expr_op == ExprOp::mul) {
            expr.getLeftPtr()->acceptVisitor(*this);
            expr.getRightPtr()->acceptVisitor(*this);
            m_compiled_steps.push_back({0, ComputeOp::mul});
        } else if (expr_op == ExprOp::div) {
            expr.getLeftPtr()->acceptVisitor(*this);
            expr.getRightPtr()->acceptVisitor(*this);
            m_compiled_steps.push_back({0, ComputeOp::div});
        } else if (expr_op == ExprOp::pow) {
            expr.getLeftPtr()->acceptVisitor(*this);
            expr.getRightPtr()->acceptVisitor(*this);
            m_compiled_steps.push_back({0, ComputeOp::pow});
        } else {
            m_compiled_steps.push_back({0, ComputeOp::nop});
        }
    }

    Models::XFunction FuncEmitter::generateFunction(std::unique_ptr<Syntax::IAstNode>& ast_root) {
        if (!ast_root) {
            return {{}};
        }

        ast_root->acceptVisitor(*this);
        return {std::move(m_compiled_steps)};
    }
}
