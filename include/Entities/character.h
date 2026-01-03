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

public:
    using base_t = Entity;

protected:
    QString name;
    Mood mood;

    Character();
    Character(const QString& name, Mood mood = Mood::Normal);

public:
    QString getName() const noexcept;
    void setName(const QString& name);

    Mood getMood() const noexcept;
    void setMood(Mood mood);
};

#include "character.ser"

#endif // CHARACTER_H
