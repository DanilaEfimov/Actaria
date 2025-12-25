#include "Entities/dialognode.h"
#include <QBuffer>
#include <QDataStream>

//TODO: normal validation
//TODO: normal documentation

namespace {
    constexpr const char* typeName = "DialogNode";
    constexpr const int fieldCount = 5;
    constexpr const int variantFieldCount = 2;

    constexpr const DialogNodeAbi order[] = {
        DialogNodeAbi::FromMessageField,   // QString (character name)
        DialogNodeAbi::MessageField,       // QString
        DialogNodeAbi::VariantsField,      // QVector<DialogNode::variant_t>
        DialogNodeAbi::ParentField,        // Entity::id_type
        DialogNodeAbi::EventField,         // Entity::id_type
    };

    /**
     * @brief toString
     * @param order
     * @return QString literal for Abi enum members
     */
    QString toString(DialogNodeAbi order) {
        switch(order) {
            case MessageField:      return QStringLiteral("MessageField");
            case FromMessageField:  return QStringLiteral("FromMessageField");
            case VariantsField:     return QStringLiteral("VariantsField");
            case ParentField:       return QStringLiteral("ParentField");
            case EventField:        return QStringLiteral("EventField");
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
        repr.append(EngineInfo::separator);
        repr.append(QString::number(static_cast<quint32>(variant.second)));
    }

    using variants_t = QVector<variant_t>;

    /**
     * @brief reprVariants
     * @param repr
     * @param variants
     */
    void reprVariants(QString& repr, const variants_t& variants){
        int size = variants.size();
        repr.append(QString::number(size));

        for(int i = 0; i < size; i++){
            repr.append(EngineInfo::separator);
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
        if(variantFieldCount * size > wordsCount - 1){  // -1 due to reading 'size'
            qWarning() << "dialognode::<namespace>::parseVariants: Not enough tokens to parse: " + QString::number(size);
            return false;
        }

        variants.clear();
        variants.reserve(size);

        int pos = 1;
        variant_t variant;
        for (int i = 0; i < size && ok; ++i) {
            variant.first = repr[pos++];
            variant.second = static_cast<Entity::id_type>(repr[pos++].toInt(&ok));
            variants.push_back(variant);
        }

        if(pos / variantFieldCount < size || !ok){
            qWarning() << "dialognode::<namespace>::parseVariants: Can not read id of entity: " + repr[(pos + variantFieldCount - 1) / variantFieldCount];
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
        return 1 + variants.size()*variantFieldCount;
    }
};

/**
 * @brief DialogNode::DialogNode
 * @param parent
 * @param event
 * @param fromMessage
 * @param message
 */
DialogNode::DialogNode(id_type parent, id_type event, QString fromMessage, QString message)
    : Entity(),
    message(message),
    fromMessage(fromMessage),
    variants(),
    parent(parent),
    event(event)
{}

/**
 * @brief DialogNode::DialogNode
 * @param data
 */
DialogNode::DialogNode(const QByteArray &data)
    : Entity(Entity::NonIncrementFlag{})
{
}

/**
 * @brief DialogNode::DialogNode
 * @param data
 */
DialogNode::DialogNode(const QStringList &data)
    : Entity(Entity::NonIncrementFlag{})
{
}

/**
 * @brief DialogNode::representField
 * @param repr
 * @param abiOrder
 */
void DialogNode::representField(QString &repr, DialogNodeAbi abiOrder) const
{
    switch(abiOrder){
        case DialogNodeAbi::MessageField:       repr += this->message; return;
        case DialogNodeAbi::FromMessageField:   repr += this->fromMessage; return;
        case DialogNodeAbi::VariantsField:      reprVariants(repr, this->variants); return;
        case DialogNodeAbi::ParentField:        repr += QString::number(this->parent); return;
        case DialogNodeAbi::EventField:         repr += QString::number(this->event); return;
    default:
        qWarning() << "DialogNode::representField: unexpected order of field: " + toString(static_cast<DialogNodeAbi>(abiOrder));
        return;
    }
}

/**
 * @brief DialogNode::readFieldFromStrings
 * @param repr
 * @param abiOrder
 * @param ok
 */
int DialogNode::readFieldFromStrings(QStringList &repr, DialogNodeAbi abiOrder, bool* ok)
{
    if(repr.empty()){
        qWarning() << "DialogNode::readFromStringField: Empty representation was given";
        *ok = false;
    }

    if(!*ok) return 0;
    switch(abiOrder){
        case DialogNodeAbi::MessageField: {
                this->message = repr[0];
                *ok = true;
                return 1;
        }
        case DialogNodeAbi::FromMessageField: {
            this->fromMessage = repr[0];
            *ok = true;
            return 1;
        }
        case DialogNodeAbi::VariantsField: {
            *ok = parseVariants(repr, this->variants);
            return wordsPerVariants(this->variants);
        }
        case DialogNodeAbi::ParentField: {
            this->parent = repr[0].toInt(ok);
            return 1;
        }
        case DialogNodeAbi::EventField: {
            this->event = repr[0].toInt(ok);
            return 1;
        }
    default:
        qWarning() << "DialogNode::readFromStringField: unexpected field: " + toString(abiOrder);
        *ok = false;
        return 0;
    }
    return 0;
}

/**
 * @brief DialogNode::dumpField
 * @param out
 * @param abiOrder
 */
void DialogNode::dumpField(QDataStream &out, DialogNodeAbi abiOrder) const
{
    switch(abiOrder){
        case DialogNodeAbi::MessageField:       out << this->message; return;
        case DialogNodeAbi::FromMessageField:   out << this->fromMessage; return;
        case DialogNodeAbi::VariantsField:      this->dumpVariants(out); return;
        case DialogNodeAbi::ParentField:        out << this->parent; return;
        case DialogNodeAbi::EventField:         out << this->event; return;
    default:
        qWarning() << "DialogNode::dumpField: unexpected order of field: " + toString(static_cast<DialogNodeAbi>(abiOrder));
        return;
    }
}

/**
 * @brief DialogNode::readField
 * @param in
 * @param abiOrder
 */
void DialogNode::readField(QDataStream &in, DialogNodeAbi abiOrder)
{
    if(in.status() != QDataStream::Ok){
        qWarning("DialogNode::readField: something went wrong, data stream unreadable");
        return;
    }

    switch(abiOrder){
        case DialogNodeAbi::MessageField:       in >> this->message; return;
        case DialogNodeAbi::FromMessageField:   in >> this->fromMessage; return;
        case DialogNodeAbi::VariantsField:      this->readVariants(in); return;
        case DialogNodeAbi::ParentField:        in >> this->parent; return;
        case DialogNodeAbi::EventField:         in >> this->event; return;
    default:
        qWarning() << "DialogNode::readField: unexpected field: " + toString(abiOrder);
        return;
    }
}

/**
 * @brief DialogNode::dumpVariant
 * @param out
 * @param variant
 * variant's fields dumping/reading in natural order
 */
void DialogNode::dumpVariant(QDataStream &out, const variant_t &variant) const
{
    out << variant.first << variant.second;
}

/**
 * @brief DialogNode::readVariant
 * @param in
 * variant's fields dumping/reading in natural order
 */
void DialogNode::readVariant(QDataStream &in)
{
    if(in.status() != QDataStream::Ok){
        qWarning("DialogNode::readVariant: something went wrong, data stream unreadable");
        return;
    }

    variant_t variant;
    in >> variant.first >> variant.second;
    this->variants.push_back(variant);
}

/**
 * @brief DialogNode::fieldSize
 * @param abiOrder
 * @return actual size of such field in bytes
 */
int DialogNode::fieldSize(DialogNodeAbi abiOrder) const noexcept
{
    int size = 0;
    switch(abiOrder){
        case DialogNodeAbi::MessageField:       size = QStringHexSize(this->message); break;
        case DialogNodeAbi::FromMessageField:   size = QStringHexSize(this->fromMessage); break;
        case DialogNodeAbi::VariantsField:      size = this->variantsSize(); break;
        case DialogNodeAbi::ParentField:        size = sizeof(this->parent); break;
        case DialogNodeAbi::EventField:         size = sizeof(this->event); break;
    default:
        qWarning() << "DialogNode::fieldSize: unexpected order of field: " + toString(static_cast<DialogNodeAbi>(abiOrder));
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
 * @brief DialogNode::isValid
 * @return
 */
bool DialogNode::isValid() const noexcept
{
    return !this->variants.empty();
}

/**
 * @brief DialogNode::getChild
 * @param variant
 * @return
 */
DialogNode::id_type DialogNode::getChild(int variant) const noexcept
{
    if(variant >= 0 && variant < this->variants.size())
        return this->variants[variant].second;
    return UNDEFINED_ID;
}

/**
 * @brief DialogNode::dumpVariants
 * @param out
 */
void DialogNode::dumpVariants(QDataStream &out) const
{
    out << static_cast<quint32>(this->variants.size());
    for(auto& variant : this->variants){
        this->dumpVariant(out, variant);
    }
}

/**
 * @brief DialogNode::readVariants
 * @param in
 */
void DialogNode::readVariants(QDataStream &in)
{
    quint32 size = 0;
    in >> size;
    this->variants.clear();
    this->variants.reserve(size);

    quint32 i = 0;
    for(; i < size; i++){
        this->readVariant(in);
    }
}
