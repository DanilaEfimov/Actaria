#ifndef DIALOGNODE_H
#define DIALOGNODE_H

#include "Entities/entity.h"
#include "Entities/context.h"

namespace abi {

    enum DialogNodeAbi {
        MessageField,       // QString
        FromMessageField,   // QString (character name)
        VariantsField,      // QVector<DialogNode::variant_t>
        ParentField,        // Entity::id_type
        EventField          // Entity::id_type
    };

};  // namespace abi

using namespace abi;

/**
 * @brief The DialogNode class
 */
class DialogNode : public Entity
{
public:
    using variant_t = QPair<QString, id_type>;

private:
    QString message;
    QString fromMessage;
    QVector<variant_t> variants;
    id_type parent;
    id_type event;

    // dump-repr stuff
    void representField(QString& repr, DialogNodeAbi abiOrder) const;
    int readFieldFromStrings(QStringList& repr, DialogNodeAbi abiOrder, bool* ok);
    void dumpField(QDataStream& out, DialogNodeAbi abiOrder) const;
    void readField(QDataStream& in, DialogNodeAbi abiOrder);
    void dumpVariant(QDataStream& out, const variant_t& variant) const;
    void readVariant(QDataStream& in);
    void dumpVariants(QDataStream& out) const;
    void readVariants(QDataStream& in);
    int fieldSize(DialogNodeAbi abiOrder) const noexcept;
    int variantsSize() const noexcept;

public:
    DialogNode(const QByteArray& data);
    DialogNode(const QStringList& data);
    DialogNode(id_type parent = UNDEFINED_ID, id_type event = UNDEFINED_ID,
               QString fromMessage = "", QString message = "");
    virtual ~DialogNode() = default;

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
