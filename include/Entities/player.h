#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/character.h"
#include "Entities/context.h"

class Player final : public Character
{
    ACT_SERIALIZABLE

public:
    static Player& instance();

    static Context experience;

private:
    explicit Player(const QString& name = {},
                    Mood mood = Mood::Normal);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

#include "player.ser"

#endif // PLAYER_H
