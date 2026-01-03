#include "Entities/player.h"


Context Player::experience{};

/**
 * @brief Player::instance
 * @return singleton reference
 */
Player& Player::instance()
{
    static Player instance;
    return instance;
}

/**
 * @brief Player::Player
 * @param name
 * @param mood
 */
Player::Player(const QString& name, Mood mood)
    : Character(name, mood)
{}
