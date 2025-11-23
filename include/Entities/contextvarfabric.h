#ifndef CONTEXTVARFABRIC_H
#define CONTEXTVARFABRIC_H

#include "utils.h"
#include "Entities/contextvar.h"

class Counter;
class NamedVar;
class Trigger;

class ContextVarFabric
{
public:
    template<typename T>
        requires utils::ContextVariable<T>
    static std::unique_ptr<T> make(VarType type, const QByteArray& data){
        switch(type){
            case VarType::Counter: return std::make_unique<Counter>(data);
            case VarType::Trigger: return std::make_unique<Trigger>(data);
            case VarType::Named: return std::make_unique<NamedVar>(data);
        default:
            return nullptr;
        }
    };
};

#endif // CONTEXTVARFABRIC_H
