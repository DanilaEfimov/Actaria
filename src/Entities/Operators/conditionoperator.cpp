#include "Entities/Operators/conditionoperator.h"


/**
 * @brief ConditionOperator::ConditionOperator
 * @param value
 * @param trueEvent
 * @param falseEvent
 */
ConditionOperator::ConditionOperator(
    bool value,
    std::shared_ptr<Event> trueEvent,
    std::shared_ptr<Event> falseEvent
)
    : Operator(),
    trueEvent(trueEvent),
    falseEvent(falseEvent),
    value(value)
{}

/**
 * @brief ConditionOperator::hash
 * @return
 */
Entity::hash_type ConditionOperator::hash() const
{
    return 42;
}

/**
 * @brief ConditionOperator::apply
 * @param context
 * @param scene
 */
bool ConditionOperator::apply(Context &context, Scene &scene)
{
    if(this->value){
        if(!this->trueEvent)
            return false;
        return this->trueEvent->exec(context, scene);
    }
    else{
        if(this->falseEvent){
            return this->falseEvent->exec(context, scene);
        }
    }

    return true;
}

/**
 * @brief ConditionOperator::type
 * @return type of this operator
 */
OperatorType ConditionOperator::type() const
{
    return OperatorType::Condition;
}
