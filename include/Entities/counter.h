#ifndef COUNTER_H
#define COUNTER_H

#include "Entities/contextvar.h"

class Counter : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = int32_t;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    Counter() = delete;
#else
    Counter() = default;
#endif
    Counter(value_type value, const QString& name);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator int() const noexcept;
};

/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Counter, V> {
    static constexpr bool is_fixed = entity_traits<ContextVar, V>::is_fixed;
    static constexpr int minimum_bytes = minimumQStringSize;
    static constexpr int maximum_bytes = unlimited;

    static constexpr const char* name = "Counter";
    static constexpr int minimum_words = 2;
    static constexpr int maximum_words = minimum_words;
};


/**
 * @brief The Writer class
 * version generalized conetext var write interface
 */
template<abi::Version V>
struct Writer<Counter, V> {
    static void write(QDataStream& out, const Counter& c) {
        out << c.value;
    }

    static void write(StringListCursor& out, const Counter& c) {
        out.append(entity_traits<Counter, V>::name);
        out.append(QString::number(c.value));
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<Counter, V> {
    static void read(QDataStream& in, Counter& c) {
        in >> c.value;
    }

    static void read(StringListCursor& in, Counter& c) {
        if(in.remaining() < entity_traits<ContextVar, V>::minimum_words){
            qWarning() << "Reader<Counter, V>: not enought words in list";
            c.value = 0;
            return;
        }

        bool ok = true;
        c.value = static_cast<Counter::value_type>(in.next().toLongLong(&ok));

        if(!ok){
            qWarning() << "Reader<Counter, V>: failed to parse value from: " << in.peek();
        }

        in.skip();    // skipping this->value field
    }
};

#endif // COUNTER_H
