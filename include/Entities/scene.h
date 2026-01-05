#ifndef SCENE_H
#define SCENE_H

#include "Entities/entity.h"

class Scene : public Entity
{
public:
    Scene();
    ~Scene() = default;

    // Entity interface
public:
    hash_type hash() const override {return 0;};
};

#endif // SCENE_H
