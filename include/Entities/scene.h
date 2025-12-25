#ifndef SCENE_H
#define SCENE_H

#include "Entities/entity.h"

class Scene : public Entity
{
public:
    Scene();
    ~Scene() = default;

    virtual QByteArray hexHeader() const override;
    virtual QStringList strHeader() const override;
};

#endif // SCENE_H
