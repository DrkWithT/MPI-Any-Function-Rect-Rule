#ifndef FUNC_EMITTER_HPP
#define FUNC_EMITTER_HPP

#include <memory>
#include <vector>
#include "Models/FunctionParts.hpp"
#include "Syntax/IAstVisitor.hpp"
#include "Syntax/IAstNode.hpp"
#include "Syntax/AstNodes.hpp"
#include "Models/XFunction.hpp"

namespace MPIRectRule::Backend {
    class FuncEmitter : public Syntax::IAstVisitor<void>{
    private:
        // todo 1: add state to compile stack-based instructions of an x-expr?
        // todo 2: implement methods.
        std::vector<Models::ComputeStep> m_compiled_steps;
        std::string m_source;

    public:
        FuncEmitter(const std::string& source);

        void visitLiteralExpr(Syntax::LiteralExpr& expr) override;

        void visitUnaryExpr(Syntax::UnaryExpr& expr) override;

        void visitBinaryExpr(Syntax::BinaryExpr& expr) override;

        [[nodiscard]] Models::XFunction generateFunction(std::unique_ptr<Syntax::IAstNode>& ast_root);
    };
}

#endif