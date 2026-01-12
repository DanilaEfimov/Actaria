#ifndef DIALOGNODE_H
#define DIALOGNODE_H

#include "Entities/entity.h"

/**
 * @brief The DialogNode class
 */
class DialogNode : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;
    using variant_t = QPair<QString, id_type>;

private:
    QVector<variant_t> variants;
    QString message;
    id_type parent;
    id_type event;
    id_type fromCharacter;

public:
    DialogNode(id_type parent = UNDEFINED_ID, id_type event = UNDEFINED_ID,
               id_type fromCharacter= UNDEFINED_ID, QString message = "");
    virtual ~DialogNode() = default;

    virtual hash_type hash() const override;

    QString getMessage() const noexcept;
    void setMessage(const QString& msg);

    id_type getEventId() const noexcept;
    void setEvent(id_type eventId);

    id_type getFromCharacter() const noexcept;
    void setFromCharacter(id_type characterId);

    void addVariant(const variant_t& variant);
    void addVariant(QString&& title, const DialogNode& variant);
    void removeChild(id_type idx);
    void clear() noexcept;

    bool hasChild(id_type variant) const noexcept;
    bool empty() const noexcept;

    id_type getChild(int variant) const noexcept;
};

#endif // DIALOGNODE_H
