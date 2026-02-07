#include "operator.ser"
#include "assignmentoperator.ser"
#include "calloperator.ser"
#include "conditionoperator.ser"
#include "jumpoperator.ser"
#include "nextoperator.ser"
#include "whileoperator.ser"
#include "returnoperator.ser"

#include "Logging/logcore.h"

/**
 * @macro SWITCH_BY_TYPES
 * Dispatches a function call based on the concrete type of an Operator object.
 *
 * Usage:
 *      SWITCH_BY_TYPES(target, obj, func, isconst);
 *
 * This macro performs the following:
 * 1. Checks the type of `obj` using obj.type().
 * 2. Calls the template function `func<ConcreteOperator, EngineInfo::defaultVersion>(target, obj)`,
 *    casting `obj` to the appropriate concrete operator type.
 * 3. Supports const and non-const objects via the `isconst` parameter.
 * 4. Triggers a fatal error if the operator type is unrecognized.
 *
 * Example:
 *      SWITCH_BY_TYPES(out, o, abi::write, const);
 *
 * Parameters:
 * @param target  The output or processing target (e.g., DataStreamCursor, StringListCursor).
 * @param obj     The Operator object (or derived type) to be dispatched.
 * @param func    The template function to call for the concrete operator type.
 * @param isconst Indicates whether to cast `obj` as a const reference.
 */
#define SWITCH_BY_TYPES(target, obj, func, isconst) \
switch ((obj).type()) { \
    case OperatorType::Assignment: \
        func<AssignmentOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst AssignmentOperator&>(obj)); \
        break; \
    case OperatorType::Call: \
        func<CallOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst CallOperator&>(obj)); \
        break; \
    case OperatorType::Condition: \
        func<ConditionOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst ConditionOperator&>(obj)); \
        break; \
    case OperatorType::Jump: \
        func<JumpOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst JumpOperator&>(obj)); \
        break; \
    case OperatorType::Next: \
        func<NextOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst NextOperator&>(obj)); \
        break; \
    case OperatorType::Return: \
        func<ReturnOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst ReturnOperator&>(obj)); \
        break; \
    case OperatorType::While: \
        func<WhileOperator, EngineInfo::defaultVersion>( \
            target, static_cast<isconst WhileOperator&>(obj)); \
        break; \
    default: \
        qFatal(logCore) << "write: undefined operator type"; \
}


/**
 * @brief Operator::Operator
 */
Operator::Operator()
    : Entity()
{}

/**
 * @brief utils::write
 * @param out
 * @param o
 */
void utils::write(DataStreamCursor &out, const Operator& o)
{
    SWITCH_BY_TYPES(out, o, abi::write, const);
}

/**
 * @brief utils::write
 * @param out
 * @param o
 */
void utils::write(StringListCursor &out, const Operator& o)
{
    SWITCH_BY_TYPES(out, o, abi::write, const);
}

/**
 * @brief utils::read
 * @param in
 * @param o
 */
void utils::read(DataStreamCursor &in, Operator& o)
{
    SWITCH_BY_TYPES(in, o, abi::read, /*non const*/);
}

/**
 * @brief utils::read
 * @param in
 * @param o
 */
void utils::read(StringListCursor &in, Operator& o)
{
    SWITCH_BY_TYPES(in, o, abi::read, /*non const*/);
}

/**
 * @brief Operator::hash
 * @return
 */
Entity::hash_type Operator::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}
