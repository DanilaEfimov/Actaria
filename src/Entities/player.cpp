#include "player.ser"


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


/**
 * @brief Player::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
Player::hash_type Player::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}
