#ifndef CONTEXTVARFABRIC_H
#define CONTEXTVARFABRIC_H

#include "utils.h"
#include "Entities/contextvar.h"

class Counter;
class NameVar;
class Trigger;

template<typename T>
    requires utils::ContextVariable<T>
struct contextvar_traits
{
    static constexpr VarType value = []() constexpr {
        if constexpr (std::is_same_v<T, NameVar>)      return VarType::Named;
        else if constexpr (std::is_same_v<T, Counter>)  return VarType::Counter;
        else if constexpr (std::is_same_v<T, Trigger>)  return VarType::Trigger;
        return VarType::Unknown;
    }();
};

class ContextVarFabric
{
public:
    template<typename T>
        requires utils::ContextVariable<T>
    static std::unique_ptr<T> make(const QByteArray& data){
        if constexpr (contextvar_traits<T>::value != VarType::Unknown){
            return std::make_unique<T>(data);
        }
        return nullptr;
    };
};

#endif // CONTEXTVARFABRIC_H
