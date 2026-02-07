#include "Entities/Operators/returnoperator.h"
#include "Entities/event.h"
#include "Entities/context.h"
#include "returnoperator.ser"


/**
 * @brief ReturnOperator::ReturnOperator
 * @param caller
 */
ReturnOperator::ReturnOperator()
    : Operator()
{}

/**
 * @brief ReturnOperator::hash
 * @return
 */
Entity::hash_type ReturnOperator::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
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
    context.popEvent();

    return true;
}
