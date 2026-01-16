#include "Compiler/contextalgebra.h"
#include "Errors/typemismatch.h"
#include "Errors/invalidargumentcount.h"
#include "Errors/invalidsignature.h"
#include "utils.h"


/**
 * @brief calculateBinary
 * @param op
 * @param l
 * @param r
 * @return  Calculated constant context value.
 */
Constant calculateBinary(ContextAlgebra op, Constant l, Constant r) {
    switch(op){
    case ContextAlgebra::Plus:
        if(typeOf(l) != typeOf(r))
            throw TypeMismatch(
                "Invalid types for Plus", typeOf(l), typeOf(r)
                );
        if(typeOf(l) == VarType::Counter)
        return std::get<int>(l) + std::get<int>(r);
        else
        return std::get<QString>(l) + std::get<QString>(r);
    case ContextAlgebra::Minus:
        return std::get<int>(l) - std::get<int>(r);
    case ContextAlgebra::Multiply:
        return std::get<int>(l) * std::get<int>(r);
    case ContextAlgebra::Divide:
        return std::get<int>(l) / std::get<int>(r);

    case ContextAlgebra::And:
        return std::get<bool>(l) && std::get<bool>(r);
    case ContextAlgebra::Or:
        return std::get<bool>(l) || std::get<bool>(r);
    case ContextAlgebra::XOr:
        return std::get<bool>(l) ^ std::get<bool>(r);
    default:
        throw InvalidArgumentCount(
            "Unexpected binary operator", argRequired(op), 2
            );
    }
}

/// BinaryOp vvv

Constant BinaryOp::evaluate() const
{
    if(argRequired(this->op) != 2)
        throw InvalidArgumentCount(
            "Binary operator requires 2 arguments",
            argRequired(this->op),
            2);

    auto l = this->left->evaluate();
    auto r = this->right->evaluate();

    if(!isValidSignature(this->op, {typeOf(l), typeOf(r)}))
        throw InvalidSignature(
            "Operation can't be calculed",
            {typeOf(l), typeOf(r)},
            this->op);

    return calculateBinary(op, l, r);
}

/// BinaryOp ^^^ / UnaryOp vvv

Constant UnaryOp::evaluate() const
{
    Constant value = this->operand->evaluate();
    switch(this->op){
    case ContextAlgebra::Not:
        if (auto* b = std::get_if<bool>(&value)) {
            return !(*b);
        }
        throw TypeMismatch(
            "invalid operand type for 'not'",
            typeOf(value),
            VarType::Trigger
            );
    default:
        throw InvalidArgumentCount(
            "Unary operation requires only 1 argument",
            argRequired(this->op),
            1
            );
    }
}

constexpr size_t argRequired(ContextAlgebra op)
{
    switch (op) {
    case ContextAlgebra::Not:
        return 1;

    case ContextAlgebra::Plus:
    case ContextAlgebra::Minus:
    case ContextAlgebra::Multiply:
    case ContextAlgebra::Divide:
    case ContextAlgebra::And:
    case ContextAlgebra::Or:
    case ContextAlgebra::XOr:
        return 2;
    }

    return 0;
}

/**
 * @brief isValidSignature
 * @param op
 * @param types
 * @return  True if signature is correct.
 *          Look at the ContextAlgebra definition in contextalgebra.h
 */
constexpr bool isValidSignature(ContextAlgebra op, std::initializer_list<VarType> types)
{
    if(types.size() != argRequired(op))
        return false;

    auto it = types.begin();
    switch(op){
    case ContextAlgebra::Not:
        return *it == VarType::Trigger;

    case ContextAlgebra::Plus:
        return *it == *(it + 1) && (*it == VarType::Counter || *it == VarType::Name);

    case ContextAlgebra::Minus:
    case ContextAlgebra::Multiply:
    case ContextAlgebra::Divide:
        return *it == *(it + 1) && *it == VarType::Counter;

    case ContextAlgebra::And:
    case ContextAlgebra::Or:
    case ContextAlgebra::XOr:
        return *it == *(it + 1) && *it == VarType::Trigger;
    }

    return 0;
}
