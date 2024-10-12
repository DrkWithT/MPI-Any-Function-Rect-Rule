/**
 * @file AstNodes.cpp
 * @author DrkWithT
 * @brief Implements AST node member functions.
 * @date 2024-10-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <utility>
#include "Syntax/AstNodes.hpp"

namespace MPIRectRule::Syntax {
    LiteralExpr::LiteralExpr(Frontend::Token& token)
    : m_token {token} {}

    ExprOp LiteralExpr::getOp() const { return ExprOp::identity; }

    const Frontend::Token& LiteralExpr::getToken() const { return m_token; }

    void LiteralExpr::acceptVisitor(IAstVisitor<void>& visitor) {
        visitor.visitLiteralExpr(*this);
    }

    UnaryExpr::UnaryExpr(std::unique_ptr<IAstNode>& inner, ExprOp op)
    : m_inner (std::move(inner)), m_op {op} {}

    UnaryExpr::UnaryExpr(std::unique_ptr<IAstNode>&& inner, ExprOp op)
    : m_inner (std::move(inner)), m_op {op} {}

    ExprOp UnaryExpr::getOp() const { return m_op; }

    void UnaryExpr::acceptVisitor(IAstVisitor<void>& visitor) {
        visitor.visitUnaryExpr(*this);
    }

    std::unique_ptr<IAstNode>& UnaryExpr::getInnerPtr() { return m_inner; }

    BinaryExpr::BinaryExpr(std::unique_ptr<IAstNode>& lhs, std::unique_ptr<IAstNode>& rhs, ExprOp op)
    : m_lhs (std::move(lhs)), m_rhs (std::move(rhs)), m_op {op} {}

    BinaryExpr::BinaryExpr(std::unique_ptr<IAstNode>&& lhs, std::unique_ptr<IAstNode>&& rhs, ExprOp op)
    : m_lhs (std::move(lhs)), m_rhs (std::move(rhs)), m_op {op} {}

    ExprOp BinaryExpr::getOp() const { return m_op; }

    void BinaryExpr::acceptVisitor(IAstVisitor<void>& visitor) {
        visitor.visitBinaryExpr(*this);
    }

    std::unique_ptr<IAstNode>& BinaryExpr::getLeftPtr() { return m_lhs; }

    std::unique_ptr<IAstNode>& BinaryExpr::getRightPtr() { return m_rhs; }
}