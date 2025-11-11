#include "scene.h"
#include "scenecontext.h"


QString Scene::getDescription() const
{
    return this->description;
}

void Scene::setDescription(const QString &description)
{
    this->description = description;
}

Scene::Scene(const QString& name)
    : Entity(name), description(""), context(nullptr) {}

