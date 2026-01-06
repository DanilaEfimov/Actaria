#include "Entities/scene.h"
#include "Entities/dialog.h"

Scene::Scene(dialog_p &&dialogp)
    :Entity(), dialog(std::move(dialogp))
{}

/**
 * @brief Scene::jump
 * @param node
 */
void Scene::jump(id_type node)
{
    this->dialog->setRoot(node);
}
