#ifndef SCENE_H
#define SCENE_H

#include "Entities/entity.h"
#include "Entities/dialog.h"

typedef QString path_t;

class SceneMeta {
    path_t description;
    path_t backgroundPath;
    path_t soundPath;

public:
    SceneMeta() = default;

    const path_t& getDescription() const;
    void setDescription(const path_t &newDescription);

    const path_t& getBackgroundPath() const;
    void setBackgroundPath(const path_t &newBackgroundPath);

    const path_t& getSoundPath() const;
    void setSoundPath(const path_t &newSoundPath);
};

class Scene : public Entity
{
    ACT_SERIALIZABLE

    using base_t = Entity;
    using dialog_p = std::unique_ptr<Dialog>;

    SceneMeta meta;
    dialog_p dialog;

public:
    Scene(dialog_p&& dialogp);
    ~Scene() = default;

    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = default;

    Dialog* getDialog() const noexcept;

    Event* getEvent(id_type event) const noexcept;

    DialogNode* getNode(id_type node) const noexcept;

    SceneMeta getMeta() const noexcept;
    SceneMeta& getMeta() noexcept;

    hash_type hash() const override;;

    void jump(id_type node);
};

#endif // SCENE_H
