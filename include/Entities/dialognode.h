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

    void collectVariants(QSet<variant_t>& all) const;
    void collectEvents(QMap<id_type, event_ptr>& all) const;
    void writeHeader(QDataStream& ret) const;

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

    QString getMessage() const noexcept;
    void setMessage(const QString& msg);

    event_ptr getEvent() const noexcept;
    void setEvent(Event* event);

    void addVariant(const variant_t& variant);
    void removeChild(int idx);
    void clear() noexcept;

    child_ptr getChild(int variant) const noexcept;

private:
    void updateContext(Context& context, int variant) const;
};

#endif // DIALOGNODE_H
