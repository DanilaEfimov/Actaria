#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Entities/entity.h"

class EventManager : public Entity
{
public:
    EventManager();
    virtual ~EventManager() = default;

    virtual QByteArray hexHeader() const;
    virtual QStringList strHeader() const;
};

#endif // EVENTMANAGER_H
