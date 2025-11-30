#ifndef PLAYER_H
#define PLAYER_H

#include "Entities/character.h"
#include "Entities/context.h"

class Builder;

class Player : public Character
{
protected:
    quint32 minimumStrings() const override;

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

    static Player& getInstance();

    void setName(const QString& name);
    QString getName() const noexcept;

    void setMood(Mood mood);
    Mood getMood() const noexcept;

    // Entity interface
    hash_type hash() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // PLAYER_H
