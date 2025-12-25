#include "Entities/dialog.h"


namespace {

    constexpr const char* typeName = "Dialog";
    constexpr const int fieldCount = 4;
    constexpr const DialogAbi order[] = {
        NodesField,     // EntityManager<DialogNode>
        EventsField,    // EntityManager<Events>
        ContextField,   // Context
        RootField,      // id_type
    };

};


Dialog::Dialog()
    : Entity(),
    nodes(),
    events(),
    root(UNDEFINED_ID)
{}


QByteArray Dialog::hexHeader() const
{

}

QStringList Dialog::strHeader() const
{

}

/**
 * @brief Dialog::action
 * @param eventId
 * @param context
 * @return true if context was changed successfully
 */
bool Dialog::action(id_type eventId, Context* context)
{
    Event* event = this->events.getObj(eventId);
    if(!event)
        return false;
    return event->exec(context);
}

/**
 * @brief Dialog::switchBranch
 * @param variant
 * @throw invalid_argument if such variant doesn't exists for current root
 * @throw logic_error if switched branch doesn't contains in this dialog
 * switch dialog branch by variant for current root
 */
void Dialog::switchBranch(int variant)
{
    DialogNode* currentRoot = this->nodes.getObj(this->root);
    id_type switchedBranch = currentRoot->getChild(variant);

    if (switchedBranch == UNDEFINED_ID) {
        throw std::invalid_argument(
            "Dialog::switchBranch: invalid variant: "
            "(root=" + std::to_string(this->root) +
            "), (variant=" + std::to_string(variant) + ")"
            );
    }

    if (!this->nodes.contains(switchedBranch)) {
        throw std::logic_error(
            "Dialog::switchBranch: chosen branch not in dialog: "
            "(root=" + std::to_string(this->root) +
            "), (switchedBranch=" + std::to_string(switchedBranch) + ")"
            );
    }

    this->root = switchedBranch;
}

