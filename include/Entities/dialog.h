#ifndef DIALOG_H
#define DIALOG_H

#include "Entities/entity.h"


class Dialog : public Entity
{
protected:
    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    Dialog();

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // DIALOG_H
