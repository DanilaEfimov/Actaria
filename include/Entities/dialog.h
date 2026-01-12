#ifndef DIALOG_H
#define DIALOG_H

#include "Entities/entity.h"
#include "Entities/dialognode.h"
#include "Entities/context.h"
#include "Entities/event.h"
#include "entitymanager.h"
#include <QHash>


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

    void setRoot(id_type newRoot);

    Event* getEvent(id_type event) const;
    void addEvent(std::unique_ptr<Event>&& event);
    void removeEvent(id_type event);
    bool containsEvent(id_type event) const noexcept;

    DialogNode* getNode(id_type node) const;
    void addNode(std::unique_ptr<DialogNode>&& node);
    void removeNode(id_type node);
    bool containsNode(id_type node) const noexcept;

    void switchBranch(id_type variant);
};

#endif // DIALOG_H
