#ifndef UTILS_H
#define UTILS_H

#include "Entities/contextvar.h"
#include "Entities/trigger.h"
#include "Entities/trigger.h"
#include "Entities/counter.h"
#include "Entities/namevar.h"

#include <QString>

using ContextValue = ContextVar::ContextValue;


namespace utils {

/**
 * @brief ContextValueTypeString
 * @param type
 * @return  Name of such context variable type,
 *          use abi::entity_traits<>
 */
QString contextValueTypeString(VarType type);

/**
 * @brief typeOf
 * @param value
 * @return  Type of context value.
 *          It is assumed that the order of the alternatives in
 *          ContextVar::ContextValue matches the values of the VarType enum.
 */
VarType typeOf(const ContextValue& value);

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

/**
 * vvv Context variable types traits section vvv
 */
template<VarType V> struct VarTypeTrait;

template<> struct VarTypeTrait<VarType::Counter> { using type = Counter::value_type; };
template<> struct VarTypeTrait<VarType::Trigger> { using type = Trigger::value_type; };
template<> struct VarTypeTrait<VarType::Name>    { using type = NameVar::value_type; };

template<VarType V>
decltype(auto) get(ContextValue& v) {
    return std::get<typename VarTypeTrait<V>::type>(v);
}
/// ^^^ Context variable types traits section ^^^

bool compare(const ContextValue& left, const ContextValue& right);
bool isSuchValue(ContextValue value, VarType type);

QString toString(const ContextValue& value);
void fromString(ContextValue& value, QString str, VarType type);

/**
 * vvv abi read/write Context value interface section vvv
 */
void writeValue(DataStreamCursor& out, const ContextValue& value);
void writeValue(StringListCursor& out, const ContextValue& value);

void readValue(DataStreamCursor& in, ContextValue& value);
void readValue(StringListCursor& in, ContextValue& value);
/// ^^^ abi read/write Context value interface section ^^^

}   // namespace utils

#endif // UTILS_H
