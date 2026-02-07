#include "Entities/Operators/conditionoperator.h"
#include "conditionoperator.ser"


/**
 * @brief ConditionOperator::ConditionOperator
 * @param value
 * @param trueEvent
 * @param falseEvent
 */
ConditionOperator::ConditionOperator(bool value, id_type trueEvent, id_type falseEvent)
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
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
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
        //return this->trueEvent->exec(context, scene);
    }
    else{
        if(this->falseEvent){
            //return this->falseEvent->exec(context, scene);
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
