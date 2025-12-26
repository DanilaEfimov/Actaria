#ifndef TRIGGER_H
#define TRIGGER_H

#include "Entities/contextvar.h"

#define TRUE_S "true"
#define FALSE_S "false"

class Trigger : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = bool;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    Trigger() = delete;
#else
    Trigger() = default;
#endif
    Trigger(value_type value, const QString& name);

    virtual ~Trigger() = default;

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator bool() const noexcept;
};


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Trigger, V> {
    static constexpr bool is_fixed = entity_traits<Trigger, V>::is_fixed;
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

    static void write(StringListCursor& out, const Trigger& t) {
        out.append(entity_traits<Trigger>::name);
        out.append(t.value ? TRUE_S : FALSE_S);
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

    static void read(StringListCursor& in, Trigger& t) {
        if(in.remaining() < entity_traits<Trigger>::minimum_words){
            qWarning() << "Reader<Trigger, V>: not enought words in list";
            t.value = false;
            return;
        }

        t.value = in.next() == TRUE_S;
        in.skip();    // skipping this->value field
    }
};

#endif // TRIGGER_H
