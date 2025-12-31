#ifndef CONTEXT_H
#define CONTEXT_H

#include "Entities/entity.h"
#include "Entities/contextvar.h"
#include "Entities/contextvarfabric.h"
#include <QMap>
#include <QScopedPointer>


class Context : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;
    using value_type = QScopedPointer<ContextVar>;

private:
    QMap<QString, value_type> context;

public:
    Context();
    Context(const QMap<QString, value_type>& context);

    qsizetype size() const;

    void merge(Context&& other);

    template<typename T>
    void update(const QString& name, T&& value){
        if(!this->context.contains(name)){
            throw std::invalid_argument("no variable named " + name.toStdString() + " in context (id=" + std::to_string(this->getId()) + ")");
        }
        this->context[name] = ContextVarFabric::make<T>(name, std::forward<T>(value));
    }
    template<typename T>
    void set(const QString& name, T&& value){
        this->context[name] = ContextVarFabric::make<T>(name, std::forward<T>(value));
    }

    void remove(const QString& name);
    void clear();
};

#include "context.ser"

#endif // CONTEXT_H
