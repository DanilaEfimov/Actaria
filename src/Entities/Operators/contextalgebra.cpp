#include "Entities/Operators/contextalgebra.h"



Constant AlgebraExpression::evaluate() const
{

}

/// AlgebraExpression ^^^ / BinaryOp vvv

Constant BinaryOp::evaluate() const
{
    auto l = this->left.evaluate();
    auto r = this->right.evaluate();
}

/// BinaryOp ^^^ / UnaryOp vvv

Constant UnaryOp::evaluate() const
{
    Constant value = this->operand.evaluate();
    switch(this->op){
    case ContextAlgebra::Not: return !std::get<bool>(value);
    default:
        return false;
    }
}
