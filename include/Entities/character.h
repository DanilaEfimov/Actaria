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
protected:
    QString name;
    Mood mood;

    Character();
    Character(const QString& name, Mood mood = Mood::Normal);
    Character(const QByteArray& data);
    Character(const QStringList& data);

    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    QString getName() const noexcept;

    // Entity interface
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // CHARACTER_H
