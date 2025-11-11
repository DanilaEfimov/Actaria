#ifndef SCENE_H
#define SCENE_H

#include "entity.h"

class SceneContext;

class Scene : public Entity
{
    QString description;
    std::unique_ptr<SceneContext> context;

public:
    Scene(const QString& name);

    QString getDescription() const;
    void setDescription(const QString &description);
};

#endif // SCENE_H
