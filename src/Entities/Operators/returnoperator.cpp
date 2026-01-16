#include "Entities/Operators/returnoperator.h"
#include "Entities/event.h"


/**
 * @brief ReturnOperator::ReturnOperator
 * @param caller
 */
ReturnOperator::ReturnOperator(Event *caller)
    : Operator(), caller(caller)
{}

/**
 * @brief ReturnOperator::hash
 * @return
 */
Entity::hash_type ReturnOperator::hash() const
{
    return 0;
}

/**
 * @brief ReturnOperator::type
 * @return type of this operator
 */
OperatorType ReturnOperator::type() const
{
    return OperatorType::Return;
}

/**
 * @brief ReturnOperator::apply
 * @param context
 * @param scene
 */
bool ReturnOperator::apply([[gnu::unused]] Context &context,
                           [[gnu::unused]] Scene &scene)
{
    return this->caller->returned = true;
}
