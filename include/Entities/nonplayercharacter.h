#ifndef NONPLAYERCHARACTER_H
#define NONPLAYERCHARACTER_H

#include "Entities/character.h"

class NonPlayerCharacter : public Character
{
private:
    QString description;

public:
    explicit NonPlayerCharacter();
    NonPlayerCharacter(const QString& name, Mood mood = Mood::Normal);
    NonPlayerCharacter(const QByteArray& data);
    NonPlayerCharacter(const QStringList& data);

    void setDescription(const QString& description);
    QString getDescription() const noexcept;
};

#endif // NONPLAYERCHARACTER_H
