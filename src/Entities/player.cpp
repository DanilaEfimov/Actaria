#include "Entities/player.h"
#include <QBuffer>

namespace {
    constexpr const char* typeName = "Player";
    constexpr const int fieldCount = 0;
};

Player Player::instance = Player("Default", Mood::Normal);
bool Player::built = false;
Context Player::inventory = Context{};

/**
 * @brief The Builder class
 */
class Builder {
public:
    /**
     * @brief BuildPlayerInstance
     *
     * @return build flag
     */
    static bool BuildPlayerInstance() {
        if(!Player::built){
            // building instance
        }
        return Player::built;
    }

    /**
     * @brief build
     *
     * @param args
     *
     * @return Player object just an object. Not instance
     */
    template<typename... Args>
    static Player build(Args... args) {
        return Player(std::forward<Args>(args)...);
    }
};

/**
 * @brief Player::Player
 *
 * @param name
 *
 * @param mood
 */
Player::Player(const QString &name, Mood mood)
    : Character(name, mood) {}

/**
 * @brief Player::Player
 *
 * @param data
 */
Player::Player(const QByteArray &data)
    : Character()
{
}

/**
 * @brief Player::Player
 *
 * @param data
 */
Player::Player(const QStringList &data)
    : Character()
{
}

/**
 * @brief Player::getInstance
 *
 * @return player instance
 */
Player &Player::getInstance()
{
    if(!Player::built){
        Player::init();
    }
    return Player::instance;
}

/**
 * @brief Player::setName
 * @param name
 */
void Player::setName(const QString &name)
{
    this->name = name;
}

/**
 * @brief Player::getName
 * @return
 */
QString Player::getName() const noexcept
{
    return this->name;
}

/**
 * @brief Player::init
 *
 * @return true if it's builded
 */
bool Player::init()
{
    return Builder::BuildPlayerInstance();
}

/**
 * @brief Player::Player
 */
Player::Player()
{
    Player::init();
}

/**
 * @brief Player::setMood
 *
 * @param mood
 */
void Player::setMood(Mood mood)
{
    this->mood = mood;
}

/**
 * @brief Player::getMood
 *
 * @return actual mood
 */
Mood Player::getMood() const noexcept
{
    return this->mood;
}
