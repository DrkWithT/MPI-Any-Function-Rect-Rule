#ifndef AST_NODES_HPP
#define AST_NODES_HPP

#include <memory>
#include "Frontend/Token.hpp"
#include "Syntax/IAstNode.hpp"

namespace MPIRectRule::Syntax {
    class LiteralExpr : public IAstNode {
    private:
        Frontend::Token m_token;

    public:
        LiteralExpr(Frontend::Token& token);

        ExprOp getOp() const override;
        const Frontend::Token& getToken() const;
        void acceptVisitor(IAstVisitor<void>& visitor) override;
    };

    class UnaryExpr : public IAstNode {
    private:
        std::unique_ptr<IAstNode> m_inner;
        ExprOp m_op;

    public:
        UnaryExpr(std::unique_ptr<IAstNode>& inner, ExprOp op);
        UnaryExpr(std::unique_ptr<IAstNode>&& inner, ExprOp op);

        ExprOp getOp() const override;
        void acceptVisitor(IAstVisitor<void>& visitor) override;

        std::unique_ptr<IAstNode>& getInnerPtr();
    };

    class BinaryExpr : public IAstNode {
    private:
        std::unique_ptr<IAstNode> m_lhs;
        std::unique_ptr<IAstNode> m_rhs;
        ExprOp m_op;

    public:
        BinaryExpr(std::unique_ptr<IAstNode>& lhs, std::unique_ptr<IAstNode>& rhs, ExprOp op);
        BinaryExpr(std::unique_ptr<IAstNode>&& lhs, std::unique_ptr<IAstNode>&& rhs, ExprOp op);

        ExprOp getOp() const override;
        void acceptVisitor(IAstVisitor<void>& visitor) override;

        std::unique_ptr<IAstNode>& getLeftPtr();
        std::unique_ptr<IAstNode>& getRightPtr();
    };
}

#endif