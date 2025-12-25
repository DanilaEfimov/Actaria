#include "Entities/trigger.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QVariant>

#define TRUE_S "true"
#define FALSE_S "false"

/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Trigger, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = minimumQStringSize;
    static constexpr int maximum_bytes = unlimited;

    static constexpr const char* name = "Trigger";
    static constexpr int minimum_words = 2;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized conetext var write interface
 */
template<abi::Version V>
struct Writer<Trigger, V> {
    static void write(QDataStream& out, const Trigger& t) {
        out << (t.value ? true : false);
    }

    static void write(QStringList& out, const Trigger& t) {
        out << entity_traits<Trigger>::name << (t.value ? TRUE_S : FALSE_S);
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<Trigger, V> {
    static void read(QDataStream& in, Trigger& t) {
        in >> t.value;
    }

    static void read(QStringList& in, Trigger& t) {
        if(in.size() < entity_traits<Trigger>::minimum_words){
            qWarning() << "Reader<Trigger, V>: not enought words in list";
            t.value = false;
            return;
        }

        t.value = in.last() == TRUE_S;
        in.removeLast();    // this->value
        in.removeLast();    // entity_traits<>::name
    }
};

/**
 * @brief Trigger::Trigger
 *
 * Normal constructor for context counter.
 *
 * @param value
 *
 * @param name
 */
Trigger::Trigger(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief Trigger::getValue
 *
 * @return trigger-value
 */
Trigger::value_type Trigger::getValue() const
{
    return this->value;
}

/**
 * @brief Trigger::setValue
 *
 * @param value
 */
void Trigger::setValue(value_type value) noexcept
{
    this->value = value;
}

/**
 * @brief Trigger::operator bool
 */
Trigger::operator bool() const noexcept
{
    return this->value;
}
