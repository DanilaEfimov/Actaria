#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/character.h"
#include "Entities/context.h"

class Builder;

class Player : public Character
{
protected:
    Player(const QString& name, Mood mood=Mood::Normal);
    Player(const QByteArray& data);
    Player(const QStringList& data);

    static Player instance;
    static bool built;
    static bool init();

public:
    friend class Builder;

    template<typename... Args>
    [[nodiscard]] static Player build(Args... args){
        return Player(std::forward<Args>(args)...);
    }

    static Context inventory;

    Player();
    virtual ~Player() = default;

    static Player& getInstance();

    void setName(const QString& name);
    QString getName() const noexcept;

    void setMood(Mood mood);
    Mood getMood() const noexcept;
};

#endif // PLAYER_H
