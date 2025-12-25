#include "Entities/contextvar.h"
#include <QBuffer>

/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Entity, V> {
    static constexpr bool is_fixed = true;
    static constexpr int minimum_bytes = sizeof(Entity::id_type);
    static constexpr int maximum_bytes = minimum_bytes;

    static constexpr const char* name = "Entity";
    static constexpr int minimum_words = 1;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized write interface
 */
template<abi::Version V>
struct Writer<ContextVar, V> {
    static void write(QDataStream& out, const ContextVar& c) {
        out << c.hexHeader().constData();
    }

    static void write(QStringList& out, const ContextVar& c) {
        out << c.strHeader();
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<ContextVar, V> {
    static void read(QDataStream& in, ContextVar& c) {
        in >> c.name;
    }

    static void read(const QStringList& in, ContextVar& c) {
        bool ok = true;
        c.id = static_cast<Entity::id_type>(in.at(0).toLongLong(&ok));

        if(!ok){
            qWarning("Reader<Entity, V>::read: can not to parse id from: %s",
                     in.empty() ? "<empty>" : in.at(0).toStdString().c_str());
        }
    }
};

ContextVar::ContextVar()
    : Entity(NonIncrementFlag{}), name() {}

ContextVar::ContextVar(const QString &name)
    : Entity(), name(name) {}

ContextVar::ContextVar(const QStringList& represent)
    : Entity(NonIncrementFlag{})
{
}

ContextVar::ContextVar(const QByteArray& represent)
    : Entity(NonIncrementFlag{})
{
}

QByteArray ContextVar::hexHeader() const
{

}

QStringList ContextVar::strHeader() const
{

}

QString ContextVar::getName() const
{
    return this->name;
}

void ContextVar::setName(const QString &name) noexcept
{
    this->name = name;
}
