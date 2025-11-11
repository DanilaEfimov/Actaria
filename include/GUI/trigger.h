#ifndef TRIGGER_H
#define TRIGGER_H

#include "entity.h"

class Trigger : public Entity
{
    bool actived = false;

public:
    Trigger(const QString& name);


};

#endif // TRIGGER_H
