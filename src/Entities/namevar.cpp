#include "Entities/namevar.h"
#include <QDataStream>

/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<NameVar, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = minimumQStringSize;
    static constexpr int maximum_bytes = unlimited;

    static constexpr const char* name = "NameVar";
    static constexpr int minimum_words = 2;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized conetext var write interface
 */
template<abi::Version V>
struct Writer<NameVar, V> {
    static void write(QDataStream& out, const NameVar& n) {
        out << n.value;
    }

    static void write(QStringList& out, const NameVar& n) {
        out << entity_traits<NameVar>::name << n.value;
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<NameVar, V> {
    static void read(QDataStream& in, NameVar& n) {
        in >> n.value;
    }

    static void read(QStringList& in, NameVar& n) {
        if(in.size() < entity_traits<NameVar>::minimum_words){
            qWarning() << "Reader<NameVar, V>: not enought words in list";
            n.value = "unknown";
            return;
        }

        n.value = in.last();
        in.removeLast();    // this->value
        in.removeLast();    // entity_traits<>::name
    }
};

/**
 * @brief NameVar::NameVar
 * @param value
 * @param name
 */
NameVar::NameVar(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief NameVar::getValue
 * @return contained value of variable
 */
NameVar::value_type NameVar::getValue() const
{
    return this->value;
}

/**
 * @brief NameVar::setValue
 * @param value
 */
void NameVar::setValue(value_type value) noexcept
{
    this->value = value;
}
