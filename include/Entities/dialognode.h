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
    DialogNode(const QByteArray& data);
    DialogNode(StringListCursor& data);
    DialogNode(id_type parent = UNDEFINED_ID, id_type event = UNDEFINED_ID,
               id_type fromCharacter= UNDEFINED_ID, QString message = "");
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


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<DialogNode, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = sizeof(Entity::id_type)*3 + sizeof(qsizetype)*2;
    static constexpr int maximum_bytes = minimum_bytes;

    static constexpr const char* name = "DialogNode";
    static constexpr int minimum_words = 5;
    static constexpr int maximum_words = unlimited;
};

/**
 * @brief The Writer class
 * version generalized write interface
 */
template<abi::Version V>
struct Writer<DialogNode, V> {
    static void write(QDataStream& out, const DialogNode& d) {
        out << d.event << d.parent << d.fromCharacter
            << d.message << static_cast<qsizetype>(d.variants.size());

        for(auto& variant : d.variants){
            out << variant.first << variant.second;
        }
    }

    static void write(StringListCursor& out, const DialogNode& d) {
        out.append(entity_traits<DialogNode, V>::name);
        out.append(QString::number(d.event));
        out.append(QString::number(d.parent));
        out.append(QString::number(d.fromCharacter));
        out.append(d.message);
        out.append(QString::number(d.variants.size()));
        for(auto& variant : d.variants){
            out.append(variant.first);
            out.append(QString::number(variant.second));
        }
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<DialogNode, V> {
    static void read(QDataStream& in, DialogNode& d) {
        in >> d.event >> d.parent >> d.fromCharacter
            >> d.message;

        qsizetype size;
        in >> size;
        d.variants.clear();
        for(qsizetype i = 0; i < size; i++){
            DialogNode::variant_t variant;
            in >> variant.first >> variant.second;
            d.variants.append(variant);
        }
    }

    static void read(StringListCursor& in, DialogNode& d) {
        bool ok = true;

        d.event = UNDEFINED_ID;
        d.parent = UNDEFINED_ID;
        d.fromCharacter = UNDEFINED_ID;
        d.message = "";
        d.variants.clear();

        qsizetype size = 0;
        if(in.remaining() < entity_traits<Entity, V>::minimum_words){
            ok = false;
        }
        else {
            d.event = static_cast<Entity::id_type>(in.next().toLongLong(&ok));
            d.parent = static_cast<Entity::id_type>(in.next().toLongLong(&ok));
            d.fromCharacter = static_cast<Entity::id_type>(in.next().toLongLong(&ok));
            d.message = in.next();
            size = in.next().toLongLong(&ok);
        }

        if(!ok){
            qWarning() << "Reader<DialogNode, V>::read: can not parse id from: " << in.peek();
        }

        for(qsizetype i = 0; ok && i < size; i++){
            DialogNode::variant_t variant;
            variant.first = in.next();
            variant.second = static_cast<Entity::id_type>(in.next().toLongLong(&ok));
        }

        if(!ok){
            qWarning() << "Reader<DialogNode, V>::read: can not parse id from: " << in.peek();
        }

        in.skip();
    }
};

#endif // DIALOGNODE_H
