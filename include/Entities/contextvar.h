/**
 * Interface for context variables: counters, triggers and names
*/

#ifndef CONTEXTVAR_H
#define CONTEXTVAR_H

#include "Entities/entity.h"

enum class VarType {
    Unknown = -1,
    Counter,
    Trigger,
    Named
};

class ContextVar : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;

protected:
    QString name;

    ContextVar();
    ContextVar(const QString& name);

public:
    virtual ~ContextVar() = default;

    QString getName() const;
    void setName(const QString& name) noexcept;
};


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

    static void write(StringListCursor& out, const ContextVar& c) {
        out.append(entity_traits<ContextVar, V>::name);
        out.append(c.name);
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

    static void read(StringListCursor& in, ContextVar& c) {
        if(in.remaining() < entity_traits<ContextVar>::minimum_words){
            qWarning() << "Reader<ContextVar, V>: not enought words in list";
            c.name = "unknown";
            return;
        }

        c.name = in.next();
        in.skip();    // skipping this->name field
    }
};

#endif // CONTEXTVAR_H
