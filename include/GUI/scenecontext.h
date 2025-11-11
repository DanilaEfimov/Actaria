#ifndef SCENECONTEXT_H
#define SCENECONTEXT_H

#include "entity.h"

// Contains metadata about background's and sound's paths
// character avatar path and so on
class MediaData;

// Contains current variants, character and current phrase
class DialogNode;


class SceneContext : public Entity
{
    using DialogRoot = DialogNode;

    std::unique_ptr<DialogRoot> dialog;
    std::unique_ptr<MediaData> media;

public:
    SceneContext(const QString& name);
};

#endif // SCENECONTEXT_H
