#include "Entities/Operators/jumpoperator.h"
#include "Entities/scene.h"
#include "Errors/nosuchid.h"
#include "jumpoperator.ser"


/**
 * @brief JumpOperator::JumpOperator
 * @param node
 */
JumpOperator::JumpOperator(id_type node)
    :Operator(), node(node)
{}

/**
 * @brief JumpOperator::hash
 * @return
 */
Entity::hash_type JumpOperator::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief JumpOperator::type
 * @return type of this operator
 */
OperatorType JumpOperator::type() const
{
    return OperatorType::Jump;
}

/**
 * @brief JumpOperator::apply
 * @param context
 * @param scene
 * @return  True if scene root updated
 */
bool JumpOperator::apply([[gnu::unused]] Context &context, Scene &scene)
{
    try{
        scene.getDialog()->setRoot(this->node);
    } catch(NoSuchId& e){
        DEBUG_ONLY(
            qDebug() << e.what();
        );
        return false;
    }

    return true;
}
