#ifndef NONPLAYERCHARACTER_H
#define NONPLAYERCHARACTER_H

#include "Entities/character.h"

class NonPlayerCharacter : public Character
{
private:
    QString description;

protected:
    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    explicit NonPlayerCharacter();
    NonPlayerCharacter(const QString& name, Mood mood = Mood::Normal);
    NonPlayerCharacter(const QByteArray& data);
    NonPlayerCharacter(const QStringList& data);

    void setDescription(const QString& description);
    QString getDescription() const noexcept;

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // NONPLAYERCHARACTER_H
