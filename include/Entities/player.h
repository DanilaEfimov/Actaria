#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/character.h"
#include "Entities/context.h"

class Player final : public Character
{
    ACT_SERIALIZABLE

private:
    explicit Player(const QString& name = {},
                    Mood mood = Mood::Normal);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

public:
    using base_t = Character;

    static Player& instance();

    static Context experience;

    virtual hash_type hash() const override;
};

#endif // PLAYER_H
