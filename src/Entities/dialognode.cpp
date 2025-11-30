#include "Entities/dialognode.h"

DialogNode::DialogNode()
    : Entity() {}


quint32 DialogNode::minimumSize() const
{
}

quint32 DialogNode::minimumStrings() const
{
}

Entity::hash_type DialogNode::hash() const
{
}

size_t DialogNode::size() const
{
}

QByteArray DialogNode::serialize() const
{
}

void DialogNode::deserialize(const QByteArray &)
{
}

QString DialogNode::represent() const
{
}

void DialogNode::fromString(const QStringList &)
{
}

DialogNode::child_ptr DialogNode::getChild(int variant) const noexcept
{
    if(variant > 0 && variant < this->variants.size())
        return this->variants[variant].second;
    return nullptr;
}

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
