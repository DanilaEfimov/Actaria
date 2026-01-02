#ifndef CONTEXT_H
#define CONTEXT_H

#include "character.h"
#include "variables"
#include <memory>
#include <unordered_map>


class Context : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;
    using contextvar_p = std::unique_ptr<ContextVar>;
    using key_t = QString;
    using value_t = contextvar_p;
    using value_types = ContextVar::ContextValue;

private:
    std::unordered_map<key_t, value_t> variables;
    std::unordered_map<key_t, Character> characters;

public:
    Context();
    Context(Context&& other);
    ~Context() = default;

    void merge(Context&& context);

    void addVariable(contextvar_p contextvar);
    void addCharacter(const Character& character);

    void removeVariable(const key_t& name);
    void removeCharacter(const key_t& name);

    bool containsVariable(const key_t& name) const noexcept;
    bool containsCharacter(const key_t& name) const noexcept;
    bool empty() const noexcept;

    void clear() noexcept;
    qsizetype size() const noexcept;

    bool equals(const QString& name, value_types value) const;
    void set(const QString& name, value_types value);
    const value_types getValue(const QString& name) const noexcept;
};

#include "context.ser"

#endif // CONTEXT_H
