#ifndef DIALOG_H
#define DIALOG_H

#include "Entities/entity.h"
#include "Entities/dialognode.h"
#include "Entities/context.h"
#include "Entities/event.h"
#include "entitymanager.h"
#include <QHash>

using namespace abi;

class Dialog : public Entity
{
    ACT_SERIALIZABLE

    EntityManager<DialogNode> nodes;
    EntityManager<Event> events;
    Context context;
    id_type root;

public:
    Dialog();
    virtual ~Dialog() = default;

    virtual hash_type hash() const override;

    bool action(id_type eventId, Context* context);
    void switchBranch(int variant);
};

#endif // DIALOG_H
