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

public:
    Character(const QString& name, Mood mood = Mood::Normal);

    QString getName() const noexcept;
    void setName(const QString& name);

    virtual hash_type hash() const override;

    Mood getMood() const noexcept;
    void setMood(Mood mood);
};

#endif // CHARACTER_H
