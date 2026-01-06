#ifndef EVENT_H
#define EVENT_H

#include "Entities/entity.h"
#include "Entities/Operators/operator.h"
#include <vector>
#include <memory>

class Context;
class Scene;
class ReturnOperator;

class Event : public Entity
{
    ACT_SERIALIZABLE

    friend class ReturnOperator;

protected:
    using operator_p = std::unique_ptr<Operator>;

    std::vector<operator_p> operators;
    bool returned = false;

public:
    using base_t = Entity;

    Event();
    Event(Event&&) = default;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    virtual ~Event() = default;

    void clear() noexcept;

    qsizetype operatorCount() const;

    void addOpertor(operator_p&& op);
    void removeOperator(qsizetype idx = 0);

    bool exec(Context& context, Scene& scene);

    hash_type hash() const override;
};

#endif // EVENT_H
