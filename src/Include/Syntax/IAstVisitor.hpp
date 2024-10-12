#ifndef I_AST_VISITOR_HPP
#define I_AST_VISITOR_HPP

namespace MPIRectRule::Syntax {
    class LiteralExpr;
    class UnaryExpr;
    class BinaryExpr;

    template <typename Rt>
    class IAstVisitor {
    public:
        virtual ~IAstVisitor() = default;

        virtual Rt visitLiteralExpr(LiteralExpr& expr) = 0;
        virtual Rt visitUnaryExpr(UnaryExpr& expr) = 0;
        virtual Rt visitBinaryExpr(BinaryExpr& expr) = 0;
    };
}

#endif