#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H

#include "parser/nodes/expression.h"
#include "lexer/token.h"

#include <QScopedPointer>

class BinaryOperation : public Expression
{
    Token op;
    QScopedPointer<Expression> left;
    QScopedPointer<Expression> right;

public:
    explicit BinaryOperation(const Token& op, Expression* left, Expression* right);

    const Token& getOperator() const;
    const Expression& getLeft() const;
    const Expression& getRight() const;
};

#endif // BINARYOPERATION_H
