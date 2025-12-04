#include "Entities/dialognode.h"

namespace {
    constexpr const char* typeName = "DialogNode";
    constexpr const int fieldCount = 4;
};

/**
 * @brief DialogNode::DialogNode
 */
DialogNode::DialogNode()
    : Entity(), parent(nullptr) {}

/**
 * @brief DialogNode::collectVariants
 * @param all
 */
void DialogNode::collectVariants(QSet<variant_t> &all) const
{

}

/**
 * @brief DialogNode::collectEvents
 * @param all
 */
void DialogNode::collectEvents(QMap<id_type, event_ptr>& all) const
{

}

/**
 * @brief DialogNode::writeHeader
 * @param out
 */
void DialogNode::writeHeader(QDataStream &out) const
{
    out << static_cast<QString>(this->message)
        << static_cast<id_type>(this->getId())
        << static_cast<id_type>(this->parent->getId())
        << static_cast<id_type>(this->onChoosen->getId());
}

/**
 * @brief DialogNode::minimumSize
 * @return
 */
quint32 DialogNode::minimumSize() const
{
    return minimumQStringSize
            + minimumQVectorSize
            + sizeof(id_type)       // parent id
            + sizeof(id_type)       // event id
            + this->Entity::minimumSize();
}

/**
 * @brief DialogNode::minimumStrings
 * @return
 */
quint32 DialogNode::minimumStrings() const
{
    return fieldCount + this->Entity::minimumStrings();
}

/**
 * @brief DialogNode::hash
 * @return
 */
Entity::hash_type DialogNode::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief DialogNode::size
 * @return
 */
size_t DialogNode::size() const
{
}

/**
 * @brief DialogNode::serialize
 * @return
 */
QByteArray DialogNode::serialize() const
{
    QSet<variant_t> allVariants;
    QMap<id_type, event_ptr> allEvents;
    this->collectVariants(allVariants);
    this->collectEvents(allEvents);

    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<quint32>(allVariants.size());
    for(auto& variant : allVariants){
        variant.second->writeHeader(out);
    }

    out << static_cast<quint32>(allEvents.size());
    QByteArray temp;
    for(auto& event : allEvents){
        temp = event->serialize();
        out.writeRawData(temp, temp.size());
    }

    QByteArray arr = this->Entity::serialize();
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

/**
 * @brief DialogNode::deserialize
 * @param data
 */
void DialogNode::deserialize(const QByteArray& data)
{
}

/**
 * @brief DialogNode::represent
 * @return
 */
QString DialogNode::represent() const
{
    QSet<variant_t> allVariants;
    QMap<id_type, event_ptr> allEvents;
    this->collectVariants(allVariants);
    this->collectEvents(allEvents);

    QStringList ret;

    ret.append(QString::number(allVariants.size()));
    for(auto& variant : allVariants){
        ret.append(variant.second->represent());
    }

    ret.append(QString::number(allEvents.size()));
    for(auto& event : allEvents){
        ret.append(event->represent());
    }

    ret.append(this->Entity::represent());
    return ret.join(separator);
}

/**
 * @brief DialogNode::fromString
 * @param data
 */
void DialogNode::fromString(const QStringList& data)
{
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
DialogNode::event_ptr DialogNode::getEvent() const noexcept
{
    return this->onChoosen;
}

/**
 * @brief DialogNode::setEvent
 * @param event
 */
void DialogNode::setEvent(Event* event)
{
    this->onChoosen = event_ptr(std::move(event));
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
 * @brief DialogNode::removeChild
 * @param idx
 */
void DialogNode::removeChild(int idx)
{
    if(idx < 0 || idx >= this->size())
        throw std::out_of_range("DialogNode::removeChild: index out of range");
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
 * @brief DialogNode::getChild
 * @param variant
 * @return
 */
DialogNode::child_ptr DialogNode::getChild(int variant) const noexcept
{
    if(variant > 0 && variant < this->variants.size())
        return this->variants[variant].second;
    return nullptr;
}

/**
 * @brief DialogNode::updateContext
 * @param context
 * @param variant
 */
void DialogNode::updateContext(Context &context, int variant) const
{
    Event* event = nullptr;
    if(this->variants.size() > variant || variant < 0){
        event = this->variants[variant].second->onChoosen.get();
        event->exec(context);
    }
    else{
        throw std::out_of_range(
            "DialogNode::updateContext: "
            "index of a variant is out of range (variant=" + std::to_string(variant) + ")"
            );
    }
}
