#ifndef FUNCTION_PARTS_HPP
#define FUNCTION_PARTS_HPP

namespace MPIRectRule::Models {
    /// @note add, sub, mul, div, and pow opcodes are binary ops.
    enum ComputeOp {
        nop,
        load_x,
        push_const,
        // pop_const,
        add,
        sub,
        mul,
        div,
        pow,
        last = pow
    };

    /// @brief Models fundamental operation on an accumulated variable value of x, assuming a stack machine.
    struct ComputeStep {
        double constant;
        ComputeOp op;
    };
}

#endif