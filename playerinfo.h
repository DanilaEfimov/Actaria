#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "entity.h"

class PlayerInfo : public Entity
{
    PlayerInfo();

public:
    static PlayerInfo& instance();

    // Entity interface
    virtual QString serialize() const override
    {
    }
    virtual void deserialize(const QString &data) override
    {
    }
};

#endif // PLAYERINFO_H
