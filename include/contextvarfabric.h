#ifndef CONTEXTVARFABRIC_H
#define CONTEXTVARFABRIC_H

#include "Entities/contextvar.h"
#include "Entities/trigger.h"       /// fro TRUE_S / FALSE_S macros
#include <memory>
#include <QString>
#include <variant>

enum class VarType;

class Counter;
class NameVar;
class Trigger;

using ContextValue = ContextVar::ContextValue;

/**
 * @brief   The ContextVariableFabric struct
 *          Provides interface of emplace-like creating
 *          variables for Context.
 */
struct ContextVariableFabric {

    using value_types = std::variant<int, bool, QString>;

    static std::unique_ptr<ContextVar> make_default(VarType type);

    static std::unique_ptr<Counter> make_counter(const QString& name, const QString& value);

    static std::unique_ptr<Trigger> make_trigger(const QString& name, const QString& value);

    static std::unique_ptr<Counter> make_counter(const QString& name, const QByteArray& value);

    static std::unique_ptr<Trigger> make_trigger(const QString& name, const QByteArray& value);

    static std::unique_ptr<NameVar> make_namevar(const QString& name, const QByteArray& value);

    static std::unique_ptr<ContextVar> make_variable(VarType type, const QString& name, const QString& value);

    static std::unique_ptr<ContextVar> make_variable(VarType type, const QString& name, const QByteArray& value);

    static std::unique_ptr<Counter> make_counter(const QString& name, int value);

    static std::unique_ptr<NameVar> make_namevar(const QString& name, const QString& value);

    static std::unique_ptr<Trigger> make_trigger(const QString& name, bool value);

    static value_types getValue(VarType type, const QString& value);
};

/**
 * @brief ContextValueTypeString
 * @param type
 * @return  Name of such context variable type,
 *          use abi::entity_traits<>
 */
QString ContextValueTypeString(VarType type);

/**
 * @brief typeOf
 * @param value
 * @return  Type of context value.
 *          It is assumed that the order of the alternatives in
 *          ContextVar::ContextValue matches the values of the VarType enum.
 */
VarType typeOf(ContextValue value);

/**
 * @brief process
 * @param action
 * @param var
 *  This function have to hide std::variant based checks.
 *  Action is lambda to process ContextVar.
 *  Action have to acts by signature (ContextValue -> Anything).
 */
template<typename Foo>
void process(Foo action, ContextVar* var) {
    auto val = var->getValue();
    std::visit([&](auto&& arg){
        action(arg);
    }, val);
}

/**
 * @brief process
 * @param action
 * @param var
 *  This function have to hide std::variant based checks.
 *  Action is lambda to process ContextValue.
 *  Action have to acts by signature (ContextValue -> Anything).
 */
template<typename Foo>
void process(Foo action, const ContextValue& var) {
    std::visit([&](auto&& arg){
        action(arg);
    }, var);
}

/**
 * @brief print
 * @param val
 */
void print(ContextValue&& val, QString message = "");
void print(const ContextValue& val, QString message = "");

/**
 * @brief context_cast
 * @param value
 *  This function have to cast values to other types.
 *  Using for some TypeMissmatch catch blocks.
 */
template<VarType T>
void context_cast(ContextValue& value) {
    std::visit([&](auto&& arg) {
        using V = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<V, int>) {
            switch(T) {
            case VarType::Trigger: value = arg != 0; break;
            case VarType::Name: value = QString::number(arg); break;
            default: return;
            }
        } else if constexpr (std::is_same_v<V, bool>) {
            switch(T) {
            case VarType::Counter: value = arg ? 1 : 0; break;
            case VarType::Name: value = arg ? TRUE_S : FALSE_S; break;
            default: return;
            }
        } else if constexpr (std::is_same_v<V, QString>) {
            switch(T) {
            case VarType::Counter: value = static_cast<int>(arg.size()); break;
            case VarType::Trigger: value = arg.isEmpty(); break;
            default: return;
            }
        }
    }, value);
}

bool compare(ContextValue left, ContextValue right);

QString toString(const ContextValue& value);
void fromString(ContextValue& value, QString str, VarType type);

void writeValue(QDataStream& out, const ContextValue& value);
void writeValue(StringListCursor& out, const ContextValue& value);

void readValue(QDataStream& in, ContextValue& value);
void readValue(StringListCursor& in, ContextValue& value);

#endif // CONTEXTVARFABRIC_H
