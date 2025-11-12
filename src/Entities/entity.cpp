#include "Entities/entity.h"


int Entity::counter = 0;

Entity::Entity()
    : id(++Entity::counter) {}

Entity::id_type Entity::getId() const
{
    return this->id;
}
