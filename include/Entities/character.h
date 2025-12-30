#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entities/entity.h"

// Every enum class must be casted
// to basic integer type for hex dumping
enum class Mood {
    Normal,
    Happy,
    Excited,
    Scared,
    Angry
};

class Character : public Entity
{
    ACT_SERIALIZABLE

protected:
    QString name;
    Mood mood;

    Character();
    Character(const QString& name, Mood mood = Mood::Normal);

public:
    QString getName() const noexcept;
    void setName(QString name);
};


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Character, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = sizeof(Entity::id_type)*3 + sizeof(qsizetype)*2;
    static constexpr int maximum_bytes = minimum_bytes;

    static constexpr const char* name = "Character";
    static constexpr int minimum_words = 5;
    static constexpr int maximum_words = unlimited;
};

/**
 * @brief The Writer class
 * version generalized write interface
 */
template<abi::Version V>
struct Writer<Character, V> {
    static void write(QDataStream& out, const Character& c) {
        out << c.name << static_cast<int>(c.mood);
    }

    static void write(StringListCursor& out, const Character& c) {
        out.append(entity_traits<Character, V>::name);
        out.append(c.name);
        out.append(QString::number(static_cast<int>(c.mood)));
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

    static void read(StringListCursor& in, Character& c) {
        c.name = "";
        c.mood = Mood::Normal;

        if(in.remaining() < entity_traits<Character, V>::minimum_words){
            qWarning() << "Reader<Character, V>::read: not enought words at cursor";
            return;
        }

        bool ok = true;
        c.name = in.next();
        c.mood = static_cast<Mood>(in.next().toInt(&ok));

        if(!ok){
            qWarning() << "Reader<Character, V>::read: can not parse mood from: " << in.peek();
        }

        in.skip();
    }
};

#endif // CHARACTER_H
