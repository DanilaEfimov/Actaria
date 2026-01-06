#include "Entities/Operators/assignmentoperator.h"
#include "utils.h"
#include "Entities/context.h"
#include "contextvar.ser"
#include "Errors/nosuchid.h"


/**
 * @brief AssignmentOperator::AssignmentOperator
 * @param lvalue
 * @param rvalue
 */
AssignmentOperator::AssignmentOperator(id_type lvalue, ContextValue rvalue)
    : Operator(), lvalue(lvalue), rvalue(rvalue)
{}

/**
 * @brief AssignmentOperator::hash
 * @return
 */
hash_type AssignmentOperator::hash() const
{
    return 1;
}

/**
 * @brief AssignmentOperator::apply
 * @param context
 * @param scene
 * @return  True if context sucessfully updated
 */
bool AssignmentOperator::apply(Context &context, [[gnu::unused]] Scene &scene)
{
    if(!context.containsVariable(this->lvalue))
        throw NoSuchId(this->lvalue, abi::entity_traits<ContextVar, EngineInfo::defaultVersion>::name);

    context.set(this->lvalue, this->rvalue);
    return true;
}
