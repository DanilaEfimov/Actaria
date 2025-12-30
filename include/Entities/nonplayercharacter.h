#ifndef NONPLAYERCHARACTER_H
#define NONPLAYERCHARACTER_H

#include "Entities/character.h"

class NonPlayerCharacter : public Character
{
    ACT_SERIALIZABLE

private:
    QString description;

public:
    explicit NonPlayerCharacter();
    NonPlayerCharacter(const QString& name, Mood mood = Mood::Normal);
    NonPlayerCharacter(const QByteArray& data);
    NonPlayerCharacter(StringListCursor& data);

    void setDescription(const QString& description);
    QString getDescription() const noexcept;
};


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<NonPlayerCharacter, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = sizeof(qsizetype);
    static constexpr int maximum_bytes = minimum_bytes;

    static constexpr const char* name = "NonPlayerCharacter";
    static constexpr int minimum_words = 1;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized write interface
 */
template<abi::Version V>
struct Writer<NonPlayerCharacter, V> {
    static void write(QDataStream& out, const NonPlayerCharacter& c) {
        out << c.description;
    }

    static void write(StringListCursor& out, const NonPlayerCharacter& c) {
        out.append(entity_traits<NonPlayerCharacter, V>::name);
        out.append(c.description);
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<NonPlayerCharacter, V> {
    static void read(QDataStream& in, NonPlayerCharacter& c) {
        in >> c.description;
    }

    static void read(StringListCursor& in, NonPlayerCharacter& c) {
        c.description = "";

        if(in.remaining() < entity_traits<NonPlayerCharacter, V>::minimum_words){
            qWarning() << "Reader<NonPlayerCharacter, V>::read: not enought words to parse";
            return;
        }

        c.description = in.next();

        in.skip();
    }
};

#endif // NONPLAYERCHARACTER_H
