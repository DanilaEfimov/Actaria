#ifndef DIALOG_H
#define DIALOG_H

#include "Entities/entity.h"
#include "Entities/dialognode.h"
#include "Entities/context.h"
#include "Entities/event.h"
#include "Entities/entitymanager.h"
#include <QHash>

namespace abi {

    enum DialogAbi {
        NodesField,     // EntityManager<DialogNode>
        EventsField,    // EntityManager<Events>
        ContextField,   // Context
        RootField,      // id_type
    };

};  // namespace abi

using namespace abi;

class Dialog : public Entity
{
    EntityManager<DialogNode> nodes;
    EntityManager<Event> events;
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

    bool action(id_type eventId, Context* context);
    void switchBranch(int variant);
};

#endif // DIALOG_H
