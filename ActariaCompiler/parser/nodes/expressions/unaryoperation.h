#ifndef UNARYOPERATION_H
#define UNARYOPERATION_H

#include "parser/nodes/expression.h"
#include "lexer/token.h"

#include <QScopedPointer>

class UnaryOperation : public Expression
{
    Token op;
    QScopedPointer<Expression> operand;

public:
    explicit UnaryOperation(const Token& op, Expression* operand);

    const Token& getOperator() const;
    const Expression& getOperand() const;
};

#endif // UNARYOPERATION_H
