#include "Entities/dialognode.h"
#include "entity.ser"
#include "dialognode.ser"
#include <QBuffer>
#include <QDataStream>


/**
 * @brief DialogNode::DialogNode
 * @param parent
 * @param event
 * @param fromCharacter
 * @param message
 */
DialogNode::DialogNode(id_type parent, id_type event, id_type fromCharacter, QString message)
    : Entity(),
    variants(),
    message(message),
    parent(parent),
    event(event),
    fromCharacter(fromCharacter)
{}

/**
 * @brief DialogNode::DialogNode
 * @param data
 */
DialogNode::DialogNode(const QByteArray &data)
    : Entity(Entity::NonIncrementFlag{})
{
    QDataStream in(data);
    abi::read<DialogNode, EngineInfo::defaultVersion>(in, *this);
}

/**
 * @brief DialogNode::DialogNode
 * @param data
 */
DialogNode::DialogNode(StringListCursor &data)
    : Entity(Entity::NonIncrementFlag{})
{
    abi::read<DialogNode, EngineInfo::defaultVersion>(data, *this);
}

/**
 * @brief DialogNode::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
DialogNode::hash_type DialogNode::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief DialogNode::getMessage
 * @return
 */
QString DialogNode::getMessage() const noexcept
{
    return this->message;
}

/**
 * @brief DialogNode::setMessage
 * @param msg
 */
void DialogNode::setMessage(const QString &msg)
{
    this->message = msg;
}

/**
 * @brief DialogNode::getEvent
 * @return
 */
DialogNode::id_type DialogNode::getEventId() const noexcept
{
    return this->event;
}

/**
 * @brief DialogNode::setEvent
 * @param event
 */
void DialogNode::setEvent(id_type event)
{
    this->event = event;
}

/**
 * @brief DialogNode::getFromCharacter
 * @return
 */
Entity::id_type DialogNode::getFromCharacter() const noexcept
{
    return this->fromCharacter;
}

/**
 * @brief DialogNode::setFromCharacter
 * @param characterId
 */
void DialogNode::setFromCharacter(id_type characterId)
{
    this->fromCharacter = characterId;
}

/**
 * @brief DialogNode::addVariant
 * @param variant
 */
void DialogNode::addVariant(const variant_t& variant)
{
    this->variants.append(variant);
}

/**
 * @brief DialogNode::addVariant
 * @param title
 * @param variant
 */
void DialogNode::addVariant(QString&& title, const DialogNode& variant)
{
    this->variants.append(variant_t(title, variant.getId()));
}

/**
 * @brief DialogNode::removeChild
 * @param idx
 */
void DialogNode::removeChild(int idx)
{
    this->variants.removeAt(idx);
}

/**
 * @brief DialogNode::clear
 */
void DialogNode::clear() noexcept
{
    this->variants.clear();
}

/**
 * @brief DialogNode::isValid
 * @return
 */
bool DialogNode::isValid() const noexcept
{
    return !this->variants.empty();
}

/**
 * @brief DialogNode::getChild
 * @param variant
 * @return
 */
DialogNode::id_type DialogNode::getChild(int variant) const noexcept
{
    if(variant >= 0 && variant < this->variants.size())
        return this->variants[variant].second;
    return UNDEFINED_ID;
}
