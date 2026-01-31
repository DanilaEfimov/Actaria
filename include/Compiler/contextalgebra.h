#ifndef CONTEXTALGEBRA_H
#define CONTEXTALGEBRA_H

#include "Entities/contextvar.h"
#include <memory>

enum class ContextAlgebra {
    Plus,       // (QString, QString) / (int, int)  -> QString / int
    Minus,      // (int, int)                       -> int
    Multiply,   // (int, int)                       -> int
    Divide,     // (int, int)                       -> int
    And,        // (bool, bool)                     -> bool
    Or,         // (bool, bool)                     -> bool
    XOr,        // (bool, bool)                     -> bool
    Not,        // bool                             -> bool
};

static constexpr size_t argRequired(ContextAlgebra);
static constexpr bool isValidSignature(ContextAlgebra, std::initializer_list<VarType>);

using Constant = ContextVar::ContextValue;

struct AlgebraExpression {
    using Evaluable = std::unique_ptr<AlgebraExpression>;

    virtual ~AlgebraExpression() = default;
    virtual Constant evaluate() const = 0;
};

struct UnaryOp final : AlgebraExpression {
    ContextAlgebra op;
    Evaluable operand;

    Constant evaluate() const override;
};

struct BinaryOp final : AlgebraExpression {
    ContextAlgebra op;
    Evaluable left;
    Evaluable right;

    Constant evaluate() const override;
};

struct Literal final : AlgebraExpression {
    Literal(Constant val)
        : AlgebraExpression(), value(val)
    {};

    Constant value;
    Constant evaluate() const override {
        return value;
    }
};

#endif // CONTEXTALGEBRA_H
