#include "Entities/character.h"
#include <QBuffer>

/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Character, V> {
    static constexpr bool is_fixed = entity_traits<Character, V>::is_fixed;
    static constexpr int minimum_bytes = minimumQStringSize;
    static constexpr int maximum_bytes = unlimited;

    static constexpr const char* name = "Character";
    static constexpr int minimum_words = 3;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized conetext var write interface
 */
template<abi::Version V>
struct Writer<Character, V> {
    static void write(QDataStream& out, const Character& c) {
        out << c.name << static_cast<int>(c.mood);
    }

    static void write(QStringList& out, const Character& c) {
        out << entity_traits<Character, V>::name << c.name << static_cast<int>(c.mood);
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<Character, V> {
    static void read(QDataStream& in, Character& c) {
        in >> c.name >> c.mood;
    }

    static void read(QStringList& in, Character& c) {
        if(in.size() < entity_traits<Character, V>::minimum_words){
            qWarning() << "Reader<Character, V>: not enought words in list";
            c.name = "unknown";
            c.mood = Mood::Normal;
            return;
        }

        c.name = in.last();
        in.removeLast();    // this->value

        bool ok = true;
        c.mood = static_cast<Mood>(in.last().toInt(&ok));
        if(!ok){
            qWarning() << "Reader<Character, V>: failed to parse value";
        }
        in.removeLast();    // entity_traits<>::name
    }
};

/**
 * @brief Character::Character
 */
Character::Character()
    : Entity(NonIncrementFlag{})
{}

/**
 * @brief Character::Character
 * @param name
 * @param mood
 */
Character::Character(const QString &name, Mood mood)
    : Entity(), name(name), mood(mood)
{}

/**
 * @brief Character::getName
 * @return name of character
 */
QString Character::getName() const noexcept
{
    return this->name;
}

/**
 * @brief Character::setName
 */
void Character::setName(QString name)
{
    this->name = name;
}
