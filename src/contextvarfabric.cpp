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
 * @param name
 * @return
 */
std::unique_ptr<ContextVar> ContextVariableFabric::make_default(VarType type, const QString &name)
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
 * @return
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
 * @brief ContextVariableFabric::make_namevar
 * @param name
 * @param value
 * @return std unique pointer to NameVar variable
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
        return false;
    }

    return false;
}
