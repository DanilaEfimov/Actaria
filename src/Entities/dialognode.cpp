#include "Entities/dialognode.h"
#include <QBuffer>
#include <QDataStream>

namespace {
    constexpr const char* typeName = "DialogNode";
    constexpr const int fieldCount = 4;

    enum Abi {
        MessageField,
        VariantsField,
        ParentField,
        EventField
    };

    constexpr const Abi order[] = {
        Abi::MessageField, Abi::VariantsField, Abi::ParentField, Abi::EventField
    };

    /**
     * @brief toString
     * @param order
     * @return QString literal for Abi enum members
     */
    QString toString(Abi order) {
        switch(order) {
            case MessageField:  return QStringLiteral("MessageField");
            case VariantsField: return QStringLiteral("VariantsField");
            case ParentField:   return QStringLiteral("ParentField");
            case EventField:    return QStringLiteral("EventField");
        default:
            return QStringLiteral("Unknown");
        }
    }

    using variant_t = DialogNode::variant_t;

    /**
     * @brief reprVariant
     * @param repr
     * @param variant
     */
    void reprVariant(QString& repr, const variant_t& variant){
        repr.append(variant.first);
        repr.append(QString::number(variant.second));
    }

    using variants_t = QVector<DialogNode::variant_t>;

    /**
     * @brief reprVariants
     * @param repr
     * @param variants
     */
    void reprVariants(QString& repr, const variants_t& variants){
        int size = variants.size();
        repr.append(QString::number(size));

        for(int i = 0; i < size; i++){
            repr.append(Entity::separator);
            reprVariant(repr, variants.at(i));
        }
    }

    /**
     * @brief parseVariants
     * @param repr
     * @param variants
     */
    bool parseVariants(const QStringList& repr, variants_t& variants){
        if(repr.empty()){
            qWarning() << "dialognode::<namespace>::parseVariants: Representation haven't required size";
            return false;
        }

        int wordsCount = repr.size();

        bool ok = false;
        int size = repr[0].toInt(&ok);
        if(!ok){
            qWarning() << "dialognode::<namespace>::parseVariants: Can not read variants size: '" + repr[0] + "'";
            return false;
        }
        if(size > wordsCount - 1){
            qWarning() << "dialognode::<namespace>::parseVariants: Not enough tokens to parse: " + QString::number(size);
            return false;
        }

        int pos = 1;
        variant_t variant;
        while (pos + 1 < wordsCount && ok) {
            variant.first = repr[pos++];
            variant.second = static_cast<Entity::id_type>(repr[pos++].toInt(&ok));
            variants.push_back(std::move(variant));
        }

        if(pos < size || !ok){
            qWarning() << "dialognode::<namespace>::parseVariants: Can not read id of entity: " + repr[pos-1];
            return false;
        }
        return true;
    }

    /**
     * @brief wordsPerVariants
     * @param variants
     * @return required size to represent variants
     */
    int wordsPerVariants(const variants_t& variants){
        return 1 + variants.size()*2;
    }
};

/**
 * @brief DialogNode::DialogNode
 * @param parent
 * @param event
 * @param message
 */
DialogNode::DialogNode(id_type parent, id_type event, QString message)
    : Entity(),
    message(message),
    variants(),
    parent(parent),
    event(event)
{}

/**
 * @brief DialogNode::DialogNode
 * @param message
 * @param parent
 * @param event
 */
DialogNode::DialogNode(QString&& message, id_type parent, id_type event)
    : Entity(),
    message(message),
    variants(),
    parent(parent),
    event(event)
{}

/**
 * @brief DialogNode::representField
 * @param repr
 * @param abiOrder
 */
void DialogNode::representField(QString &repr, int abiOrder) const
{
    if(abiOrder < 0 || abiOrder >= fieldCount){
        qWarning() << "DialogNode::representField: invalid field order: " + QString::number(abiOrder);
        return;
    }

    switch(static_cast<Abi>(abiOrder)){
        case Abi::MessageField:  repr += this->message; return;
        case Abi::VariantsField: reprVariants(repr, this->variants); return;
        case Abi::ParentField:   repr += QString::number(this->parent); return;
        case Abi::EventField:    repr += QString::number(this->event); return;
    default:
        qWarning() << "DialogNode::representField: unexpected order of field: " + toString(static_cast<Abi>(abiOrder));
        return;
    }
}

/**
 * @brief DialogNode::readFromStringField
 * @param repr
 * @param abiOrder
 * @param ok
 */
void DialogNode::readFromStringField(QStringList &repr, int abiOrder, bool* ok)
{
    if(abiOrder < 0 || abiOrder >= fieldCount){
        qWarning() << "DialogNode::readFromStringField: invalid field order: " + QString::number(abiOrder);
        *ok = false;
    }

    if(repr.empty()){
        qWarning() << "DialogNode::readFromStringField: Empty representation was given";
        *ok = false;
    }

    if(!*ok) return;
    switch(static_cast<Abi>(abiOrder)){
        case Abi::MessageField:  this->message = repr[0]; return;
        case Abi::VariantsField: *ok = parseVariants(repr, this->variants); return;
        case Abi::ParentField:   this->parent = repr[0].toInt(ok); return;
        case Abi::EventField:    this->event = repr[0].toInt(ok); return;
    default:
        qWarning() << "DialogNode::readFromStringField: unexpected order of field: " + toString(static_cast<Abi>(abiOrder));
        *ok = false;
        return;
    }
    *ok = true;
}

/**
 * @brief DialogNode::dumpField
 * @param out
 * @param abiOrder
 */
void DialogNode::dumpField(QDataStream &out, int abiOrder) const
{
    if(abiOrder < 0 || abiOrder >= fieldCount){
        qWarning() << "DialogNode::dumpField: invalid field order: " + QString::number(abiOrder);
        return;
    }

    switch(static_cast<Abi>(abiOrder)){
        case Abi::MessageField:  out << this->message; return;
        case Abi::VariantsField: this->dumpVariants(out); return;
        case Abi::ParentField:   out << this->parent; return;
        case Abi::EventField:    out << this->event; return;
    default:
        qWarning() << "DialogNode::dumpField: unexpected order of field: " + toString(static_cast<Abi>(abiOrder));
        return;
    }
}

/**
 * @brief DialogNode::readField
 * @param in
 * @param abiOrder
 */
void DialogNode::readField(QDataStream &in, int abiOrder)
{
    if(abiOrder < 0 || abiOrder >= fieldCount){
        qWarning() << "DialogNode::readField: invalid field order: " + QString::number(abiOrder);
        return;
    }

    try{
        switch(static_cast<Abi>(abiOrder)){
            case Abi::MessageField:  in >> this->message; return;
            case Abi::VariantsField: this->readVariants(in); return;
            case Abi::ParentField:   in >> this->parent; return;
            case Abi::EventField:    in >> this->event; return;
        default:
            qWarning("DialogNode::readField: unexpected order of field");
            return;
        }
    }
    catch(...){
        qWarning() << "DialogNode::readField: can not read field at position: "  + toString(static_cast<Abi>(abiOrder));
        return;
    }
}

/**
 * @brief DialogNode::fieldSize
 * @param abiOrder
 * @return actual size of such field in bytes
 */
int DialogNode::fieldSize(int abiOrder) const noexcept
{
    if(abiOrder < 0 || abiOrder >= fieldCount){
        qWarning() << "DialogNode::fieldSize: invalid field order: " + QString::number(abiOrder);
        return 0;
    }

    int size = 0;
    switch(static_cast<Abi>(abiOrder)){
        case Abi::MessageField: size = QStringHexSize(this->message); break;
        case Abi::VariantsField: size = this->variantsSize(); break;
        case Abi::ParentField: size = sizeof(this->parent); break;
        case Abi::EventField: size = sizeof(this->event); break;
    default:
        qWarning() << "DialogNode::fieldSize: unexpected order of field: " + toString(static_cast<Abi>(abiOrder));
    }

    return size;
}

/**
 * @brief DialogNode::variantsSize
 * @return actual size of this->variants in bytes
 */
int DialogNode::variantsSize() const noexcept
{
    int size = 0;
    size = minimumQVectorSize;
    for(int i = 0; i < this->variants.size(); i++){
        size += QStringHexSize(this->variants.at(i).first);
        size += sizeof(this->variants.at(i).second);    // fixed size
    }
    return size;
}

/**
 * @brief DialogNode::minimumSize
 * @return minimum required size to deserialize in bytes
 */
quint32 DialogNode::minimumSize() const
{
    return minimumQStringSize
            + minimumQVectorSize
            + sizeof(this->parent)
            + sizeof(this->event)
            + this->Entity::minimumSize();
}

/**
 * @brief DialogNode::minimumStrings
 * @return
 */
quint32 DialogNode::minimumStrings() const
{
    return fieldCount + this->Entity::minimumStrings();
}

/**
 * @brief DialogNode::hash
 * @return
 */
Entity::hash_type DialogNode::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief DialogNode::size
 * @return actual size of *this in bytes
 */
size_t DialogNode::size() const
{
    int size = 0;
    for(auto field : order){
        size += this->fieldSize(field);
    }

    size += this->Entity::size();
    return size;
}

/**
 * @brief DialogNode::serialize
 * @return
 */
QByteArray DialogNode::serialize() const
{
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    for(auto idx : order){
        this->dumpField(out, static_cast<int>(idx));
    }

    QByteArray arr = this->Entity::serialize();
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

/**
 * @brief DialogNode::deserialize
 * @param data
 */
void DialogNode::deserialize(const QByteArray& data)
{
    if(data.size() < this->DialogNode::minimumSize()){
        qWarning("Entity::deserialize: data too small");
        return;
    }

    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    // reversed order
    for(int i = 0; i < fieldCount; i++){
        this->readField(in, fieldCount - 1 - i);
    }

    quint64 pos = buffer.pos();
    this->Entity::deserialize(data.mid(pos));
}

/**
 * @brief DialogNode::represent
 * @return human readable representation of *this
 */
QString DialogNode::represent() const
{
    QString repr = typeName;
    for(auto idx : order){
        repr.append(Entity::separator);
        this->representField(repr, idx);
    }
    repr.append(Entity::separator);
    repr.append(this->Entity::represent());
    return repr;
}

/**
 * @brief DialogNode::fromString
 * @param data
 */
void DialogNode::fromString(const QStringList& data)
{
    int pos = 0;
    int field = 0;
    bool ok = false;
    QStringList repr = data;
    for(; field < fieldCount; field++){
        repr = repr.mid(pos);
        this->readFromStringField(repr, field, &ok);
        if(!ok) break;
    }
    if(field < fieldCount - 1){
        qWarning() << "DialogNode::fromString: Parsing was aborted at filed " + QString::number(field);
        return;
    }
    this->Entity::fromString(repr.mid(1));  // skipp typeName
}

/**
 * @brief DialogNode::getMessage
 * @return
 */
QString DialogNode::getMessage() const noexcept
{
    return this->message;
}

/**
 * @brief DialogNode::setMessage
 * @param msg
 */
void DialogNode::setMessage(const QString &msg)
{
    this->message = msg;
}

/**
 * @brief DialogNode::getEvent
 * @return
 */
DialogNode::id_type DialogNode::getEventId() const noexcept
{
    return this->event;
}

/**
 * @brief DialogNode::setEvent
 * @param event
 */
void DialogNode::setEvent(id_type event)
{
    this->event = event;
}

/**
 * @brief DialogNode::addVariant
 * @param variant
 */
void DialogNode::addVariant(const variant_t& variant)
{
    this->variants.append(variant);
}

/**
 * @brief DialogNode::addVariant
 * @param title
 * @param variant
 */
void DialogNode::addVariant(QString&& title, const DialogNode& variant)
{
    this->variants.append(variant_t(title, variant.getId()));
}

/**
 * @brief DialogNode::removeChild
 * @param idx
 */
void DialogNode::removeChild(int idx)
{
    this->variants.removeAt(idx);
}

/**
 * @brief DialogNode::clear
 */
void DialogNode::clear() noexcept
{
    this->variants.clear();
}

/**
 * @brief DialogNode::getChild
 * @param variant
 * @return
 */
DialogNode::id_type DialogNode::getChild(int variant) const noexcept
{
    if(variant > 0 && variant < this->variants.size())
        return this->variants[variant].second;
    return static_cast<id_type>(-1);
}

/**
 * @brief DialogNode::dumpVariants
 * @param out
 */
void DialogNode::dumpVariants(QDataStream &out) const
{
    for(auto& variant : this->variants){
        out << variant.first << variant.second;
    }
}

/**
 * @brief DialogNode::readVariants
 * @param in
 */
void DialogNode::readVariants(QDataStream &in)
{
    QVector<variant_t> vec;
    quint32 size = 0;
    in >> size;

    QString message;
    id_type variantId;
    try{
        for(int i = 0; i < size; i++){
            in >> message >> variantId;
            vec.push_back(
                variant_t(std::move(message), variantId)
            );
        }
    }
    catch(...){
        qWarning() << "DialogNode::readVariants: can not read variant at position: " + QString::number(size);
        return;
    }

    this->variants = std::move(vec);
}
