#ifndef I_AST_NODE_HPP
#define I_AST_NODE_HPP

#include "Frontend/Token.hpp"
#include "Syntax/IAstVisitor.hpp"

namespace MPIRectRule::Syntax {
    enum class ExprOp {
        add,
        sub,
        mul,
        div,
        pow,
        negate,
        identity,
        unknown,
        last = unknown
    };

    class IAstNode {
    public:
        virtual ~IAstNode() = default;

        virtual ExprOp getOp() const = 0;
        virtual void acceptVisitor(IAstVisitor<void>& visitor) = 0;
    };
}

#endif