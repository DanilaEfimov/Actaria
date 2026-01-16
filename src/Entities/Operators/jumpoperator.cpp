#include "Entities/Operators/jumpoperator.h"
#include "Entities/scene.h"
#include "Errors/nosuchid.h"


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
    return 1;
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
