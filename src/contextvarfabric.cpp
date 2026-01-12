#include "counter.ser"
#include "trigger.ser"
#include "namevar.ser"
#include "contextvarfabric.h"


/**
 * @brief ContextVariableFabric::make_counter
 * @param name
 * @param value
 * @return std unique pointer to Counter variable
 */
std::unique_ptr<Counter> ContextVariableFabric::make_counter(const QString &name, const QByteArray &value)
{
    int counter = 0;
    QDataStream(value) >> counter;
    return std::make_unique<Counter>(counter, name);
}

/**
 * @brief ContextVariableFabric::make_namevar
 * @param name
 * @param value
 * @return std unique pointer to NameVar variable
 */
std::unique_ptr<Trigger> ContextVariableFabric::make_trigger(const QString &name, const QByteArray &value)
{
    bool trigger = false;
    QDataStream(value) >> trigger;
    return std::make_unique<Trigger>(trigger, name);
}

/**
 * @brief ContextVariableFabric::make_trigger
 * @param name
 * @param value
 * @return std unique pointer to Trigger variable
 */
std::unique_ptr<NameVar> ContextVariableFabric::make_namevar(const QString &name, const QByteArray &value)
{
    return std::make_unique<NameVar>(QString(value), name);
}

/**
 * @brief ContextVariableFabric::make_default
 * @param type
 * @return  a std unique pointer to default constructed
 *          context variable of type 'type'
 */
std::unique_ptr<ContextVar> ContextVariableFabric::make_default(VarType type)
{
    switch(type){
    case VarType::Counter:  return std::make_unique<Counter>(Counter({},{}));
    case VarType::Name:     return std::make_unique<NameVar>(NameVar({},{}));
    case VarType::Trigger:  return std::make_unique<Trigger>(Trigger({},{}));
    default:
        qWarning() << "ContextVariableFabric::make_default: unknown type: " << QString::number(static_cast<int>(type));
        return nullptr;
    }
}

/**
 * @brief ContextVariableFabric::make_trigger
 * @param name
 * @param value
 * @return
 */
std::unique_ptr<Counter> ContextVariableFabric::make_counter(const QString &name, const QString &value)
{
    bool ok = true;
    int val = value.toInt(&ok);
    if(!ok){
        qWarning() << "ContextVariableFabric::make_counter: failed to parse int from: " << value;
        return nullptr;
    }

    return std::make_unique<Counter>(val, name);
}

/**
 * @brief ContextVariableFabric::make_trigger
 * @param name
 * @param value
 * @return
 */
std::unique_ptr<Trigger> ContextVariableFabric::make_trigger(const QString &name, const QString &value)
{
    bool trigger = (value == TRUE_S);
    return std::make_unique<Trigger>(trigger, name);
}

/**
 * @brief ContextVariableFabric::getValue
 * @param value
 * @return std optional int or bool
 */
std::unique_ptr<ContextVar> ContextVariableFabric::make_variable(VarType type, const QString& name, const QString &value)
{
    switch(type){
    case VarType::Counter: return ContextVariableFabric::make_counter(name, value);
    case VarType::Name: return ContextVariableFabric::make_namevar(name, value);
    case VarType::Trigger: return ContextVariableFabric::make_trigger(name, value);
    default:
        return nullptr;
    }
}

/**
 * @brief ContextVariableFabric::make_counter
 * @param name
 * @param value
 * @return std unique pointer to Counter variable
 */
std::unique_ptr<ContextVar> ContextVariableFabric::make_variable(VarType type, const QString& name, const QByteArray &value)
{
    switch(type){
    case VarType::Counter: return ContextVariableFabric::make_counter(name, value);
    case VarType::Name: return ContextVariableFabric::make_namevar(name, value);
    case VarType::Trigger: return ContextVariableFabric::make_trigger(name, value);
    default:
        return nullptr;
    }
}

/**
 * @brief ContextVariableFabric::make_counter
 * @param name
 * @param value
 * @return
 */
std::unique_ptr<Counter> ContextVariableFabric::make_counter(const QString& name, int value)
{
    return std::make_unique<Counter>(value, name);
}

/**
 * @brief ContextVariableFabric::make_namevar
 * @param name
 * @param value
 * @return std unique pointer to NameVar variable
 */
std::unique_ptr<NameVar> ContextVariableFabric::make_namevar(const QString& name, const QString& value)
{
    return std::make_unique<NameVar>(value, name);
}

/**
 * @brief ContextVariableFabric::make_trigger
 * @param name
 * @param value
 * @return
 */
std::unique_ptr<Trigger> ContextVariableFabric::make_trigger(const QString& name, bool value)
{
    return std::make_unique<Trigger>(value, name);
}

/**
 * @brief ContextVariableFabric::getValue
 * @param type
 * @param value
 * @return  Constant context value parsed from string.
 */
ContextVariableFabric::value_types ContextVariableFabric::getValue(VarType type, const QString &value)
{
    switch(type){
    case VarType::Counter: {
        bool ok = true;
        int res = value.toInt(&ok);
        if(!ok)
            qWarning() << "ContextVariableFabric::getValue: failed to parse int from: " << value;
        return res;
    } break;
    case VarType::Trigger: {
        bool res = value == TRUE_S;
        return res;
    } break;
    case VarType::Name:
        return value;
    default:
        qWarning() << "ContextVariableFabric::getValue: unknown context variable type: " << static_cast<int>(type);
        return false;
    }

    return false;
}

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

    switch(typeOf(left)){
    case VarType::Counter: return std::get<int>(left) == std::get<int>(right);
    case VarType::Name: return std::get<QString>(left) == std::get<QString>(right);
    case VarType::Trigger: return std::get<bool>(left) == std::get<bool>(right);
    default:
        qDebug() << "compare: unknown variable type";
        return false;
    }
}
