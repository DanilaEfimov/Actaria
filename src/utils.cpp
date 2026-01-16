#include "utils.h"

#include "counter.ser"
#include "namevar.ser"
#include "trigger.ser"


QString ContextValueTypeString(VarType type) {
    switch(type){
    case VarType::Counter:  return abi::entity_traits<Counter, EngineInfo::defaultVersion>::name;
    case VarType::Trigger:  return abi::entity_traits<Trigger, EngineInfo::defaultVersion>::name;
    case VarType::Name:     return abi::entity_traits<NameVar, EngineInfo::defaultVersion>::name;
    default:
        return "Unknown";
    }
}

VarType typeOf(ContextVar::ContextValue value) {
    return static_cast<VarType>(value.index());
}

void print(ContextValue&& val, QString message)
{
    std::visit([&](auto&& arg){
        qDebug() << message << arg;
    }, val);
}

void print(const ContextValue &val, QString message)
{
    std::visit([&](auto&& arg){
        qDebug() << message << arg;
    }, val);
}

void writeValue(QDataStream &out, const ContextValue &value)
{
    int type = static_cast<int>(typeOf(value));
    out << type;
    process([&](auto&& arg){
        out << arg;
    }, value);
}

void writeValue(StringListCursor &out, const ContextValue &value)
{
    out.append(QString::number(static_cast<int>(typeOf(value))));
    out.append(toString(value));
}

QString toString(const ContextValue &value)
{
    QString res = "";

    switch(typeOf(value)){
    case VarType::Counter:
        res = QString::number(std::get<static_cast<int>(VarType::Counter)>
                              (value));
    case VarType::Trigger:
        res = QString(std::get<static_cast<int>(VarType::Trigger)>
                          (value) ? TRUE_S : FALSE_S);
    case VarType::Name:
        res = std::get<static_cast<int>(VarType::Name)>
            (value);
    default:
        qDebug() << "toString: undefined type";
        res = "";
    }

    return res;
}

void readValue(QDataStream &in, ContextValue &value)
{
    int type = -1;
    in >> type;

    QString strval;
    int intval;
    bool trigger;

    switch(static_cast<VarType>(type)){
    case VarType::Name: in >> strval; value = strval; return;
    case VarType::Trigger: in >> trigger; value = trigger; return;
    case VarType::Counter: in >> intval; value = intval; return;
    default: return;
    }
}

void readValue(StringListCursor &in, ContextValue &value)
{
    VarType type = static_cast<VarType>(in.peek().toInt());
    fromString(value, in.next(), type);
}

void fromString(ContextValue &value, QString str, VarType type)
{
    switch(type){
    case VarType::Name: value = str; return;
    case VarType::Trigger: value = str == TRUE_S; return;
    case VarType::Counter: value = str.toInt(); return;
    default: return;
    }
}

bool compare(ContextValue left, ContextValue right)
{
    if(typeOf(left) != typeOf(right))
        return false;

    using counter_value_t = Counter::value_type;
    using namevar_value_t = NameVar::value_type;
    using trigger_value_t = Trigger::value_type;


    switch(typeOf(left)){
    case VarType::Counter: return std::get<counter_value_t>(left) == std::get<counter_value_t>(right);
    case VarType::Name: return std::get<namevar_value_t>(left) == std::get<namevar_value_t>(right);
    case VarType::Trigger: return std::get<trigger_value_t>(left) == std::get<trigger_value_t>(right);
    default:
        qDebug() << "compare: unknown variable type";
        return false;
    }
}

bool isSuchValue(ContextValue value, VarType type)
{
    return typeOf(value) == type;
}
