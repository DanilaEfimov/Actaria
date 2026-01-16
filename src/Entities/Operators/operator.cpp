#include "operator.ser"
#include "assignmentoperator.ser"
#include "calloperator.ser"
#include "conditionoperator.ser"
#include "jumpoperator.ser"
#include "nextoperator.ser"
#include "whileoperator.ser"
#include "returnoperator.ser"


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
        qFatal("write: undefined operator type"); \
}


/**
 * @brief Operator::Operator
 */
Operator::Operator()
    : Entity()
{}

void fix::write(QDataStream &out, const Operator& o)
{
    SWITCH_BY_TYPES(out, o, abi::write, const);
}

void fix::write(StringListCursor &out, const Operator& o)
{
    SWITCH_BY_TYPES(out, o, abi::write, const);
}

void fix::read(QDataStream &in, Operator& o)
{
    SWITCH_BY_TYPES(in, o, abi::read, /*non const*/);
}

void fix::read(StringListCursor &in, Operator& o)
{
    SWITCH_BY_TYPES(in, o, abi::read, /*non const*/);
}
