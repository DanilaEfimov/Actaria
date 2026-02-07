#include "utils.h"

#include "counter.ser"
#include "namevar.ser"
#include "trigger.ser"

#include "datastreamcursor.h"
#include "Logging/logcore.h"


/**
 * @brief utils::contextValueTypeString
 * @param type
 * @return
 */
QString utils::contextValueTypeString(VarType type) {
    switch(type){
    case VarType::Counter:  return abi::entity_traits<Counter, EngineInfo::defaultVersion>::name;
    case VarType::Trigger:  return abi::entity_traits<Trigger, EngineInfo::defaultVersion>::name;
    case VarType::Name:     return abi::entity_traits<NameVar, EngineInfo::defaultVersion>::name;
    default:
        qWarning(logCore) << "utils::contextValueTypeString: unknown type";
        return "unknown";
    }
}

/**
 * @brief utils::typeOf
 * @param value
 * @return
 */
VarType utils::typeOf(const ContextVar::ContextValue& value) {
    return static_cast<VarType>(value.index());
}

/**
 * @brief print
 * @param val
 * @param message
 */
void print(ContextValue&& val, QString message)
{
    if(logCore().isDebugEnabled()) return;

    std::visit([&](auto&& arg){
        qDebug(logCore) << message << arg;
    }, val);
}

/**
 * @brief utils::print
 * @param val
 * @param message
 */
void utils::print(const ContextValue &val, QString message)
{
    if(logCore().isDebugEnabled()) return;

    std::visit([&](auto&& arg){
        qDebug(logCore) << message << arg;
    }, val);
}

/**
 * @brief utils::writeValue
 * @param out
 * @param value
 */
void utils::writeValue(DataStreamCursor &out, const ContextValue &value)
{
    int type = static_cast<int>(utils::typeOf(value));
    out << type;
    utils::process([&](auto&& arg){
        out << arg;
    }, value);
}

/**
 * @brief utils::writeValue
 * @param out
 * @param value
 */
void utils::writeValue(StringListCursor &out, const ContextValue &value)
{
    int type = static_cast<int>(typeOf(value));
    out.append(QString::number(type));
    out.append(toString(value));
}

/**
 * @brief utils::toString
 * @param value
 * @return
 */
QString utils::toString(const ContextValue &value)
{
    QString res = "";

    switch(typeOf(value)){
    case VarType::Counter:
        res = QString::number(std::get<static_cast<int>(VarType::Counter)>
                              (value)); break;
    case VarType::Trigger:
        res = QString(std::get<static_cast<int>(VarType::Trigger)>
                          (value) ? TRUE_S : FALSE_S); break;
    case VarType::Name:
        res = std::get<static_cast<int>(VarType::Name)>
            (value); break;
    default:
        qWarning(logCore) << "utils::toString: undefined type: " << static_cast<int>(typeOf(value));
        res = "";
    }

    return res;
}

/**
 * @brief utils::readValue
 * @param in
 * @param value
 */
void utils::readValue(DataStreamCursor &in, ContextValue &value)
{
    int type = -1;
    in >> type;

    QString strval;
    int intval;
    bool trigger;

    switch(static_cast<VarType>(type)){
    case VarType::Name:
        in >> strval; value = strval; return;
    case VarType::Trigger:
        in >> trigger; value = trigger; return;
    case VarType::Counter:
        in >> intval; value = intval; return;
    default:
        qWarning(logCore) << "utils::readValue: undefined type: " << static_cast<int>(type);
        return;
    }
}

/**
 * @brief utils::readValue
 * @param in
 * @param value
 */
void utils::readValue(StringListCursor &in, ContextValue &value)
{
    VarType type = static_cast<VarType>(in.peek().toInt());
    fromString(value, in.next(), type);
}

/**
 * @brief utils::fromString
 * @param value
 * @param str
 * @param type
 */
void utils::fromString(ContextValue &value, QString str, VarType type)
{
    switch(type){
    case VarType::Name:
        value = str; return;
    case VarType::Trigger:
        value = str == TRUE_S; return;
    case VarType::Counter:
        value = str.toInt(); return;
    default:
        qWarning(logCore) << "utils::fromString: undefined type: " << static_cast<int>(type);
        return;
    }
}

/**
 * @brief utils::compare
 * @param left
 * @param right
 * @return
 */
bool utils::compare(const ContextValue& left, const ContextValue& right)
{
    if(typeOf(left) != typeOf(right))
        return false;

    return left == right;
}

/**
 * @brief utils::isSuchValue
 * @param value
 * @param type
 * @return
 */
bool utils::isSuchValue(ContextValue value, VarType type)
{
    return typeOf(value) == type;
}
