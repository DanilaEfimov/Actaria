#include "playerinfo.h"

PlayerInfo::PlayerInfo()
    : Entity("PlayerInfo") {}

PlayerInfo &PlayerInfo::instance()
{
    static PlayerInfo playerInfo = PlayerInfo();
    return playerInfo;
}
