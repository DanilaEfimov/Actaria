#include "gamecontext.h"

GameContext::GameContext()
    : Entity("GameContext") {}

GameContext &GameContext::instance()
{
    static GameContext context = GameContext();
    return context;
}

QString GameContext::serialize() const
{
    return "";
}

void GameContext::deserialize(const QString &data)
{

}
