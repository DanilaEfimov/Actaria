#include "Entities/scene.h"
#include "Entities/dialog.h"
#include "dialognode.ser"
#include "Errors/nosuchid.h"


/**
 * @brief Scene::Scene
 * @param dialogp
 */
Scene::Scene(dialog_p&& dialogp)
    :Entity(), dialog(std::move(dialogp))
{}

/**
 * @brief Scene::getDialog
 * @return
 */
Dialog *Scene::getDialog() const noexcept
{
    return this->dialog.get();
}

/**
 * @brief Scene::getEvent
 * @param event
 * @return
 */
Event *Scene::getEvent(id_type event) const noexcept
{
    return this->dialog->getEvent(event);
}

/**
 * @brief Scene::getNode
 * @param node
 * @return
 */
DialogNode* Scene::getNode(id_type node) const noexcept
{
    return this->dialog->getNode(node);
}

/**
 * @brief Scene::getMeta
 * @return  scene meta data reference (background image path e.g.)
 */
SceneMeta Scene::getMeta() const noexcept
{
    return this->meta;
}

/**
 * @brief Scene::getMeta
 * @return non-const scene metadata reference
 */
SceneMeta& Scene::getMeta() noexcept
{
    return this->meta;
}

/**
 * @brief Scene::hash
 * @return
 */
Entity::hash_type Scene::hash() const {
    return 0;
}

/**
 * @brief Scene::jump
 * @param node
 */
void Scene::jump(id_type node)
{
    if(!this->dialog->containsNode(node))
        throw NoSuchId(node, abi::entity_traits<DialogNode, EngineInfo::defaultVersion>::name);

    this->dialog->setRoot(node);
}

/**
 * @brief SceneMeta::getDescription
 * @return
 */
const path_t& SceneMeta::getDescription() const
{
    return this->description;
}

/**
 * @brief SceneMeta::setDescription
 * @param newDescription
 */
void SceneMeta::setDescription(const path_t &newDescription)
{
    this->description = newDescription;
}

/**
 * @brief SceneMeta::getBackgroundPath
 * @return
 */
const path_t& SceneMeta::getBackgroundPath() const
{
    return this->backgroundPath;
}

/**
 * @brief SceneMeta::setBackgroundPath
 * @param newBackgroundPath
 */
void SceneMeta::setBackgroundPath(const path_t& newBackgroundPath)
{
    this->backgroundPath = newBackgroundPath;
}

/**
 * @brief SceneMeta::getSoundPath
 * @return
 */
const path_t& SceneMeta::getSoundPath() const
{
    return this->soundPath;
}

/**
 * @brief SceneMeta::setSoundPath
 * @param newSoundPath
 */
void SceneMeta::setSoundPath(const path_t &newSoundPath)
{
    this->soundPath = newSoundPath;
}
