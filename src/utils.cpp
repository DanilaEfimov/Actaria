#include "utils.h"

#include "counter.ser"
#include "namevar.ser"
#include "trigger.ser"


QString utils::ContextValueTypeString(VarType type) {
    switch(type){
    case VarType::Counter:  return abi::entity_traits<Counter, EngineInfo::defaultVersion>::name;
    case VarType::Trigger:  return abi::entity_traits<Trigger, EngineInfo::defaultVersion>::name;
    case VarType::Name:     return abi::entity_traits<NameVar, EngineInfo::defaultVersion>::name;
    default:
        return "Unknown";
    }
}

VarType utils::typeOf(const ContextVar::ContextValue& value) {
    return static_cast<VarType>(value.index());
}

void print(ContextValue&& val, QString message)
{
    std::visit([&](auto&& arg){
        qDebug() << message << arg;
    }, val);
}

void utils::print(const ContextValue &val, QString message)
{
    std::visit([&](auto&& arg){
        qDebug() << message << arg;
    }, val);
}

void utils::writeValue(QDataStream &out, const ContextValue &value)
{
    int type = static_cast<int>(utils::typeOf(value));
    out << type;
    utils::process([&](auto&& arg){
        out << arg;
    }, value);
}

void utils::writeValue(StringListCursor &out, const ContextValue &value)
{
    int type = static_cast<int>(typeOf(value));
    out.append(QString::number(type));
    out.append(toString(value));
}

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
        qDebug() << "toString: undefined type";
        res = "";
    }

    return res;
}

void utils::readValue(QDataStream &in, ContextValue &value)
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
        qDebug() << "readValue: undefined type";
        return;
    }
}

void utils::readValue(StringListCursor &in, ContextValue &value)
{
    VarType type = static_cast<VarType>(in.peek().toInt());
    fromString(value, in.next(), type);
}

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
        qDebug() << "fromString: undefined type";
        return;
    }
}

bool utils::compare(const ContextValue& left, const ContextValue& right)
{
    if(typeOf(left) != typeOf(right))
        return false;

    return left == right;
}

bool utils::isSuchValue(ContextValue value, VarType type)
{
    return typeOf(value) == type;
}
