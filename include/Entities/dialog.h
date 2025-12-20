#ifndef DIALOG_H
#define DIALOG_H

#include "Entities/entity.h"
#include "Entities/dialognode.h"
#include "Entities/context.h"
#include <QHash>


class Dialog : public Entity
{
    QHash<id_type, DialogNode> nodes;
    Context context;
    id_type root;

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

    void switchBranch(int variant);
};

#endif // DIALOG_H
