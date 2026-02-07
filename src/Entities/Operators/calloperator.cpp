#include "Entities/Operators/calloperator.h"
#include "Entities/scene.h"
#include "calloperator.ser"


/**
 * @brief CallOperator::CallOperator
 * @param eventId
 */
CallOperator::CallOperator(id_type eventId)
    : Operator(), event(eventId)
{}

/**
 * @brief CallOperator::hash
 * @return
 */
Entity::hash_type CallOperator::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief CallOperator::apply
 * @param context
 * @param scene
 */
bool CallOperator::apply(Context &context, Scene &scene)
{
    auto toCall = scene.getEvent(this->event);

    return toCall->exec(context, scene);
}

/**
 * @brief CallOperator::type
 * @return type of this operator
 */
OperatorType CallOperator::type() const
{
    return OperatorType::Call;
}
