#ifndef DIALOGNODE_H
#define DIALOGNODE_H

#include "Entities/entity.h"
#include "Entities/event.h"

/**
 * @brief The DialogNode class
 */
class DialogNode : public Entity
{
public:
    using parent_ptr = QSharedPointer<DialogNode>;
    using child_ptr = QSharedPointer<DialogNode>;
    using event_ptr = QSharedPointer<Event>;
    using variant_t = QPair<QString, id_type>;

private:
    QString message;
    QVector<variant_t> variants;
    id_type parent;
    id_type event;

    // dump-repr stuff
    void representField(QString& repr, int abiOrder) const;
    int readFieldFromStrings(QStringList& repr, int abiOrder, bool* ok);
    void dumpField(QDataStream& out, int abiOrder) const;
    void readField(QDataStream& in, int abiOrder);
    void dumpVariant(QDataStream& out, const variant_t& variant) const;
    void readVariant(QDataStream& in);
    void dumpVariants(QDataStream& out) const;
    void readVariants(QDataStream& in);
    int fieldSize(int abiOrder) const noexcept;
    int variantsSize() const noexcept;

protected:
    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    DialogNode(const QByteArray& data);
    DialogNode(const QStringList& data);
    DialogNode(id_type parent, id_type event, QString message = "");
    explicit DialogNode(QString&& message, id_type parent, id_type event);

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;

    QString getMessage() const noexcept;
    void setMessage(const QString& msg);

    id_type getEventId() const noexcept;
    void setEvent(id_type eventId);

    void addVariant(const variant_t& variant);
    void addVariant(QString&& title, const DialogNode& variant);
    void removeChild(int idx);
    void clear() noexcept;
    bool isValid() const noexcept;

    id_type getChild(int variant) const noexcept;
};

#endif // DIALOGNODE_H
