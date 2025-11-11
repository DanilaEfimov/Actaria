#include "entity.h"

int Entity::count = 0;

Entity::Entity(const QString &name)
    : name(name)
{
    this->id = ++Entity::count;
}

Entity::~Entity() {}

QString Entity::getName() const
{
    return this->name;
}

int Entity::getId() const
{
    return this->id;
}

size_t Entity::typeHash() const noexcept
{
    return typeid(*this).hash_code();
}

bool Entity::operator<(const Entity &other) const
{
    return this->id < other.id;
}

bool Entity::operator>(const Entity &other) const
{
    return this->id > other.id;
}
