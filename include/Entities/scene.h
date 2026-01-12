#ifndef SCENE_H
#define SCENE_H

#include "Entities/dialog.h"

struct SceneMeta {
    QString backgroundPath;
    QString description;
};

class Scene : public Entity
{
    ACT_SERIALIZABLE

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

    hash_type hash() const override;;

    void jump(id_type node);
};

#endif // SCENE_H
