#ifndef NONPLAYERCHARACTER_H
#define NONPLAYERCHARACTER_H

#include "Entities/character.h"

class NonPlayerCharacter : public Character
{
    ACT_SERIALIZABLE

private:
    QString description;

public:
    NonPlayerCharacter();
    NonPlayerCharacter(const QString& name, Mood mood = Mood::Normal);
    NonPlayerCharacter(const QByteArray& data);
    NonPlayerCharacter(StringListCursor& data);

    void setDescription(const QString& description);
    QString getDescription() const noexcept;
};

#include "nonplayercharacter.ser"

#endif // NONPLAYERCHARACTER_H
