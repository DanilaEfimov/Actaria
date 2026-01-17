#ifndef CONTEXT_H
#define CONTEXT_H

#include "character.h"
#include "variables"
#include <memory>
#include <unordered_map>
#include <stack>

class Event;

class Context : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;
    using contextvar_p = std::unique_ptr<ContextVar>;
    using key_t = Entity::id_type;
    using value_t = contextvar_p;
    using value_types = ContextVar::ContextValue;
    using event_ptr = std::shared_ptr<Event>;

private:
    std::unordered_map<key_t, value_t> variables;
    std::unordered_map<key_t, Character> characters;
    std::stack<event_ptr> callStack;

public:
    Context();
    Context(Context&& other);
    ~Context() = default;

    virtual hash_type hash() const override;

    void merge(Context&& context);

    int stackDepth() const noexcept;
    event_ptr top() const noexcept;
    bool stackEmpty() const noexcept;
    void pushEvent(event_ptr event);
    void popEvent();

    void addVariable(contextvar_p contextvar);
    void addCharacter(const Character& character);

    void removeVariable(const key_t& name);
    void removeCharacter(const key_t& name);

    bool containsVariable(const key_t& name) const noexcept;
    bool containsCharacter(const key_t& name) const noexcept;
    bool empty() const noexcept;

    void clear() noexcept;
    qsizetype size() const noexcept;

    bool equals(const key_t& name, value_types value) const;
    void set(const key_t& name, value_types value);
    const value_types getValue(const key_t& name) const;
};

#endif // CONTEXT_H
