#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entities/entity.h"

class Character : public Entity
{
protected:
    QString name;

    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    Character() = delete;
    Character(const QString& name);
    Character(const QStringList& represent);
    Character(const QByteArray& represent);

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // CHARACTER_H
