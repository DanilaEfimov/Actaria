#include "Entities/Operators/nextoperator.h"


/**
 * @brief NextOperator::NextOperator
 * @param newScene
 */
NextOperator::NextOperator(Scene* newScene)
    :Operator(), next(nullptr)
{
    if(!newScene)
        throw std::invalid_argument("NextOperator::NextOperator: new scene pointer can not be nullptr");

    this->next = newScene;
}

/**
 * @brief NextOperator::hash
 * @return
 */
Entity::hash_type NextOperator::hash() const
{
    return 0;
}

/**
 * @brief NextOperator::apply
 * @param context
 * @param scene
 * @return True if scene was updated
 */
bool NextOperator::apply([[gnu::unused]] Context& context, Scene& scene)
{
    if(&scene == this->next)
        return false;

    scene = std::move(*this->next);
    return true;
}
