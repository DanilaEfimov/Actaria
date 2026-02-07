#include "Entities/Operators/nextoperator.h"
#include "nextoperator.ser"


/**
 * @brief NextOperator::NextOperator
 * @param newScene
 */
NextOperator::NextOperator(id_type newScene)
    : Operator(),
    next(newScene)
{}

/**
 * @brief NextOperator::hash
 * @return
 */
Entity::hash_type NextOperator::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief NextOperator::type
 * @return type of this operator
 */
OperatorType NextOperator::type() const
{
    return OperatorType::Next;
}

/**
 * @brief NextOperator::apply
 * @param context
 * @param scene
 * @return True if scene was updated
 */
bool NextOperator::apply([[gnu::unused]] Context& context, Scene& scene)
{
}
