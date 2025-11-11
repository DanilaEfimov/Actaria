#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "entity.h"

class PlayerInfo;

class GameContext : public Entity
{
    GameContext();

public:
    static GameContext& instance();

    // Entity interface
    virtual QString serialize() const override;
    virtual void deserialize(const QString &data) override;
};

#endif // GAMECONTEXT_H
