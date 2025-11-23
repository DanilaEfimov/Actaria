#include "Entities/player.h"
#include <QBuffer>

namespace {
    constexpr const char* typeName = "Player";
    constexpr const int fieldCount = 0;
};

Player Player::instance = Player("Default", Mood::Normal);
bool Player::built = false;

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
 * @brief Player::minimumStrings
 *
 * @return
 */
quint32 Player::minimumStrings() const
{
    return fieldCount + this->Character::minimumStrings();
}

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
    this->deserialize(data);
}

/**
 * @brief Player::Player
 *
 * @param data
 */
Player::Player(const QStringList &data)
    : Character()
{
    this->fromString(data);
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

/**
 * @brief Player::hash
 *
 * @return fnva1 hash by typename
 */
Entity::hash_type Player::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Player::serialize
 *
 * @return hex dump of player instance
 */
QByteArray Player::serialize() const
{
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    QByteArray arr = Player::instance.Character::serialize();
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

/**
 * @brief Player::deserialize
 *
 * @param data
 */
void Player::deserialize(const QByteArray& data)
{
    this->Character::deserialize(data);
}

/**
 * @brief Player::represent
 *
 * @return QString representation of instance
 */
QString Player::represent() const
{
    return QStringList{
        typeName,
        Player::instance.Character::represent()
    }.join(separator);
}

/**
 * @brief Player::fromString
 *
 * @param data
 */
void Player::fromString(const QStringList& data)
{
    this->Character::fromString(data.mid(fieldCount));
}
