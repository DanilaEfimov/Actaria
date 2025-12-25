#include "Entities/contextvar.h"

/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<ContextVar, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = minimumQStringSize;
    static constexpr int maximum_bytes = unlimited;

    static constexpr const char* name = "ContextVar";
    static constexpr int minimum_words = 2;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized conetext var write interface
 */
template<abi::Version V>
struct Writer<ContextVar, V> {
    static void write(QDataStream& out, const ContextVar& c) {
        out << c.name;
    }

    static void write(QStringList& out, const ContextVar& c) {
        out << entity_traits<ContextVar>::name << c.name;
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

    static void read(QStringList& in, ContextVar& c) {
        if(in.size() < entity_traits<ContextVar>::minimum_words){
            qWarning() << "Reader<ContextVar, V>: not enought words in list";
            c.name = "unknown";
            return;
        }

        c.name = in.last();
        in.removeLast();    // this->name
        in.removeLast();    // entity_traits<>::name
    }
};

/**
 * @brief ContextVar::ContextVar
 */
ContextVar::ContextVar()
    : Entity(NonIncrementFlag{}), name() {}

/**
 * @brief ContextVar::ContextVar
 * @param name
 */
ContextVar::ContextVar(const QString &name)
    : Entity(), name(name) {}

/**
 * @brief ContextVar::getName
 * @return name of variable
 */
QString ContextVar::getName() const
{
    return this->name;
}

/**
 * @brief ContextVar::setName
 * @param name
 */
void ContextVar::setName(const QString &name) noexcept
{
    this->name = name;
}
