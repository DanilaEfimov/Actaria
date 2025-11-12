#include "Entities/entity.h"
#include "utils.h"


int Entity::counter = 0;

Entity::Entity()
    : id(++Entity::counter) {}

uint64_t Entity::hash() const
{
    return fnv1a_64("Entity", 6);
}

int Entity::getId() const
{
    return this->id;
}
