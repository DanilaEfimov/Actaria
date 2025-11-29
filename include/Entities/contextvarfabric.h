#ifndef CONTEXTVARFABRIC_H
#define CONTEXTVARFABRIC_H

#include "utils.h"
#include "Entities/contextvar.h"
#include "Entities/counter.h"
#include "Entities/namevar.h"
#include "Entities/trigger.h"


/**
 * @brief The vartype_traits class
 */
template<typename T>
struct vartype_traits {
    static constexpr VarType value = []() -> VarType {
        if constexpr (std::is_same_v<T, Trigger::value_type>){
            return VarType::Trigger;
        }
        else if constexpr (std::is_same_v<T, Counter::value_type>){
            return VarType::Counter;
        }
        else if constexpr (std::is_same_v<T, NameVar::value_type>){
            return VarType::Named;
        }
        return VarType::Unknown;
    }();
};

class ContextVarFabric
{
public:
    /**
     * @brief make
     * @param data
     * @return
     */
    template<typename T>
        requires utils::ContextVariable<T>
    static std::unique_ptr<ContextVar> make(const QByteArray& data){
        return std::make_unique<T>(data);
    };

    /**
     * @brief make
     * @param data
     * @return
     */
    template<typename T>
        requires utils::ContextVariable<T>
    static std::unique_ptr<ContextVar> make(const QStringList& data){
        return std::make_unique<T>(data);
    };

    /**
     * @brief make
     * @param name
     * @param value
     * @return
     */
    template<typename T>
    static std::unique_ptr<ContextVar> make(const QString& name, T&& value){
        constexpr auto type = vartype_traits<T>::value;
        switch(type){
            case VarType::Counter: return std::make_unique<Counter>(name, std::forward<T>(value));
            case VarType::Trigger: return std::make_unique<Trigger>(name, std::forward<T>(value));
            case VarType::Named: return std::make_unique<NameVar>(name, std::forward<T>(value));
        default:
            return nullptr;
        }
    }
};

#endif // CONTEXTVARFABRIC_H
