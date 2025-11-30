#include "Entities/event.h"

namespace {
    constexpr const char* typeName = "Event";
    constexpr int fieldCount = 1;
};

quint32 Event::minimumSize() const
{
}

/**
 * @brief Event::minimumStrings
 * @return
 */
quint32 Event::minimumStrings() const
{
    return fieldCount + this->Entity::minimumStrings();
}

/**
 * @brief Event::hash
 * @return
 */
hash_type Event::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Event::size
 * @return
 */
size_t Event::size() const
{
    size_t size = sizeof(this->onEvent.size());
    for(const auto& op : this->onEvent){
        size += op->size();
    }
    size += this->Event::size();
    return size;
}

/**
 * @brief Event::serialize
 * @return
 */
QByteArray Event::serialize() const
{
}

void Event::deserialize(const QByteArray &)
{
}

QString Event::represent() const
{
}

void Event::fromString(const QStringList &)
{
}
