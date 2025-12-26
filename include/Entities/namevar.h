#ifndef NAMEVAR_H
#define NAMEVAR_H

#include "Entities/contextvar.h"

class NameVar : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = QString;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    NameVar() = delete;
#else
    NameVar() = default;
#endif
    NameVar(value_type value, const QString& name);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator QString() const noexcept;
};


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<NameVar, V> {
    static constexpr bool is_fixed = entity_traits<NameVar, V>::is_fixed;
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

    static void write(StringListCursor& out, const NameVar& n) {
        out.append(entity_traits<NameVar>::name);
        out.append(n.value);
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

    static void read(StringListCursor& in, NameVar& n) {
        if(in.remaining() < entity_traits<NameVar>::minimum_words){
            qWarning() << "Reader<NameVar, V>: not enought words in list";
            n.value = "unknown";
            return;
        }

        n.value = in.next();
        in.skip();    // skipping this->value field
    }
};

#endif // NAMEVAR_H
