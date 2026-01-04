#ifndef CONTEXTALGEBRA_H
#define CONTEXTALGEBRA_H

#include "Entities/contextvar.h"
#include <variant>
#include <memory>

enum class ContextAlgebra {
    Plus,       // (QString, QString) / (int, int)  -> QString / int
    Minus,      // (int, int)                       -> int
    Multiply,   // (int, int)                       -> int
    Divide,     // (int, int)                       -> int
    And,        // (bool, bool)                     -> bool
    Or,         // (bool, bool)                     -> bool
    XOr,        // (bool, bool)                     -> bool
    Not,        // x: bool                          -> !x
};

using Constant = ContextVar::ContextValue;

struct BinaryOp;
struct UnaryOp;

class AlgebraExpression {
    using Evaluable = std::variant<
        std::unique_ptr<UnaryOp>, std::unique_ptr<BinaryOp>>;

    Evaluable value;

public:
    AlgebraExpression(const AlgebraExpression&) = delete;
    AlgebraExpression& operator=(const AlgebraExpression&) = delete;

    AlgebraExpression(AlgebraExpression&&) noexcept = default;
    AlgebraExpression& operator=(AlgebraExpression&&) noexcept = default;

    Constant evaluate() const;
};

struct UnaryOp {
    ContextAlgebra op;
    AlgebraExpression operand;

    Constant evaluate() const;
};

struct BinaryOp {
    ContextAlgebra op;
    AlgebraExpression left;
    AlgebraExpression right;

    Constant evaluate() const;
};

#endif // CONTEXTALGEBRA_H
