#include "dialog.ser"


Dialog::Dialog()
    : Entity(),
    nodes(),
    events(),
    root(UNDEFINED_ID)
{}

/**
 * @brief Dialog::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
Dialog::hash_type Dialog::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
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
    return true; //event->exec(context);
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

