#ifndef CONTEXT_H
#define CONTEXT_H

#include "Entities/entity.h"
#include "Entities/contextvar.h"
#include "Entities/contextvarfabric.h"
#include <QMap>

class Context : public Entity
{
public:
    using value_type = std::unique_ptr<ContextVar>;

private:
    QMap<QString, value_type> context;

protected:
    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    Context();
    Context(const QMap<QString, value_type> context);

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;

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
};

#endif // CONTEXT_H
