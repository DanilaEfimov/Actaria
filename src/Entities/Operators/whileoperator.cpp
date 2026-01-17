#include "Entities/Operators/whileoperator.h"
#include "Entities/context.h"
#include "utils.h"
#include "Errors/typemismatch.h"


/**
 * @brief WhileOperator::WhileOperator
 * @param variable
 * @param body
 */
WhileOperator::WhileOperator(id_type variable, id_type body)
    : Operator(),
    body(body),
    toCompare(variable)
{}

/**
 * @brief WhileOperator::hash
 * @return
 */
Entity::hash_type WhileOperator::hash() const
{
    return 0;
}

/**
 * @brief WhileOperator::apply
 * @param context
 * @param scene
 */
bool WhileOperator::apply(Context &context, Scene &scene)
{
    bool res = true;

    ContextValue val = context.getValue(this->toCompare);

    if(utils::typeOf(val) != VarType::Trigger)
        throw TypeMismatch(
            "WhileOperator::apply: variable have to be a Trigger",
            utils::typeOf(val), VarType::Trigger
            );

    while(std::get<Trigger::value_type>(val)){
        //res &= this->body->exec(context, scene);
        val = context.getValue(this->toCompare);
    }

    return res;
}

/**
 * @brief WhileOperator::type
 * @return type of this operator
 */
OperatorType WhileOperator::type() const
{
    return OperatorType::While;
}
