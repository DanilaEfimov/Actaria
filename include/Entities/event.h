#ifndef EVENT_H
#define EVENT_H

#include "Entities/entity.h"
#include "Entities/Operators/operator.h"
#include <QVector>
#include <memory>

class Context;
class Scene;

class Event : public Entity
{
    ACT_SERIALIZABLE

protected:
    using operator_p = std::unique_ptr<Operator>;

    QVector<operator_p> operators;

public:
    using base_t = Entity;

    Event();
    Event(Event&&) = default;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    virtual ~Event() = default;

    void clear() noexcept;

    qsizetype operatorCount() const;

    virtual bool exec(Context& context, Scene& scene) = 0;
};

#endif // EVENT_H
