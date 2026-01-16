#include "assignmentoperator.ser"
#include "common.h"
#include "Entities/context.h"
#include "contextvar.ser"
#include "Errors/nosuchid.h"


/**
 * @brief AssignmentOperator::AssignmentOperator
 * @param lvalue
 * @param rvalue
 */
AssignmentOperator::AssignmentOperator(id_type lvalue, ContextValue rvalue)
    : Operator(),
    lvalue(lvalue),
    rvalue(rvalue)
{}

/**
 * @brief AssignmentOperator::hash
 * @return
 */
hash_type AssignmentOperator::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief AssignmentOperator::type
 * @return type of this operator
 */
OperatorType AssignmentOperator::type() const
{
    return OperatorType::Assignment;
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
