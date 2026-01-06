#include "Entities/Operators/conditionoperator.h"


/**
 * @brief ConditionOperator::ConditionOperator
 * @param value
 * @param trueEvent
 * @param falseEvent
 */
ConditionOperator::ConditionOperator(
    bool value,
    std::unique_ptr<Event> trueEvent,
    std::unique_ptr<Event> falseEvent
)
    : Operator(),
    trueEvent(std::move(trueEvent)),
    falseEvent(std::move(falseEvent)),
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
