#ifndef DIALOGNODE_H
#define DIALOGNODE_H

#include "Entities/entity.h"
#include "Entities/event.h"


class DialogNode : public Entity
{
    using parent_ptr = std::shared_ptr<DialogNode>;
    using child_ptr = std::shared_ptr<DialogNode>;
    using event_ptr = std::shared_ptr<Event>;
    using variant_t = std::pair<QString, child_ptr>;

    QString message;
    parent_ptr parent;
    QVector<variant_t> variants;
    event_ptr onChoosen;

protected:
    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    DialogNode();

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;

    child_ptr getChild(int variant) const noexcept;

private:
    void updateContext(Context& context, int variant) const;
};

#endif // DIALOGNODE_H
