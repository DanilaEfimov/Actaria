#include "dialog.ser"
#include "dialognode.ser"
#include "event.ser"
#include "Errors/nosuchid.h"


/**
 * @brief Dialog::Dialog
 */
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
 * @brief Dialog::setRoot
 * @param newRoot
 * @throw NoSuchId exception
 */
void Dialog::setRoot(id_type newRoot)
{
    if(!this->nodes.contains(newRoot))
        throw NoSuchId(newRoot, abi::entity_traits<DialogNode, EngineInfo::defaultVersion>::name);

    this->root = newRoot;
}

/**
 * @brief Dialog::getEvent
 * @param event
 * @return
 */
Event *Dialog::getEvent(id_type event) const
{
    if(!this->containsEvent(event))
        throw NoSuchId(event, abi::entity_traits<Event, EngineInfo::defaultVersion>::name);

    return this->events.getObj(event);
}

/**
 * @brief Dialog::addEvent
 * @param event
 */
void Dialog::addEvent(std::unique_ptr<Event>&& event)
{
    this->events.addObj(event.release());
}

void Dialog::removeEvent(id_type event)
{
    this->events.removeObj(event);
}

/**
 * @brief Dialog::containsEvent
 * @param event
 * @return
 */
bool Dialog::containsEvent(id_type event) const noexcept
{
    return this->events.contains(event);
}

/**
 * @brief Dialog::getNode
 * @param node
 * @return
 */
DialogNode *Dialog::getNode(id_type node) const
{
    if(!this->containsNode(node))
        throw NoSuchId(node, abi::entity_traits<DialogNode, EngineInfo::defaultVersion>::name);

    return this->nodes.getObj(node);
}

/**
 * @brief Dialog::addNode
 * @param node
 */
void Dialog::addNode(std::unique_ptr<DialogNode> &&node)
{
    this->nodes.addObj(node.release());
}

/**
 * @brief Dialog::removeNode
 * @param node
 */
void Dialog::removeNode(id_type node)
{
    this->nodes.removeObj(node);
}

/**
 * @brief Dialog::containsNode
 * @param node
 * @return
 */
bool Dialog::containsNode(id_type node) const noexcept
{
    return this->nodes.contains(node);
}

/**
 * @brief Dialog::switchBranch
 * @param variant
 */
void Dialog::switchBranch(id_type variant)
{
    if(!this->nodes.contains(variant))
        throw NoSuchId(variant, abi::entity_traits<DialogNode, EngineInfo::defaultVersion>::name);

    this->root = variant;
}

