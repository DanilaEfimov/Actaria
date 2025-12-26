/**
 * @file readwrite.h
 * here declared interface of reading and writing
 * engine entities as byte array and string
*/

#ifndef READWRITE_H
#define READWRITE_H

#include "utils.h"
#include "engineinfo.h"
#include "stringlistcursor.h"
#include <type_traits>
#include <QByteArray>
#include <QDataStream>
#include <QStringList>

/**
 * @macro ACT_SERIALIZABLE
 * Marks a class as serializable in the ABI system.
 *
 * Usage:
 *   class MyClass {
 *       ACT_SERIALIZABLE
 *       ...
 *   };
 *
 * This macro declares friendship with the abi::Writer and abi::Reader
 * templates for all versions, allowing serialization and deserialization
 * of the class without exposing private members.
 */
#define ACT_SERIALIZABLE \
    template <utils::GameEntity T, abi::Version V> \
    friend struct abi::entity_traits; \
    template <typename T, abi::Version V> \
    friend struct abi::Writer; \
    template <typename T, abi::Version V> \
    friend struct abi::Reader; \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::write(QDataStream&, const T&); \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::write(StringListCursor&, const T&); \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::read(QDataStream&, T&); \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::read(StringListCursor&, T&);


namespace abi {

static constexpr int unlimited = -1;

/**
 * @brief The entity_traits class
 */
template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
struct entity_traits {
    static_assert(sizeof(T) == 0, "abi::entity_traits<T, V>: specialization required");

    static constexpr bool is_fixed = std::is_fundamental_v<T>;
    static constexpr int minimum_bytes = sizeof(T);
    static constexpr int maximum_bytes = sizeof(T);

    static constexpr const char* name = typeid(T).name();
    static constexpr int minimum_words = 1;
    static constexpr int maximum_words = unlimited;
};

/**
 * @brief The Writer class
 */
template <typename T, Version V = EngineInfo::defaultVersion>
struct Writer {
    static_assert(sizeof(T) == 0, "abi::Writer<T, V>: specialization required");

    static void write(QDataStream&, const T&);
    static void write(StringListCursor&, const T&);
};

/**
 * @brief The Reader class
 * read methods returns offset of readed data
 */
template <typename T, Version V = EngineInfo::defaultVersion>
struct Reader {
    static_assert(sizeof(T) == 0, "abi::Reader<T, V>: specialization required");

    static void read(QDataStream&, T&);
    static void read(StringListCursor&, T&);
};


/**
 * @brief The Writer class
 */
template <FundamentalType T, Version V>
struct Writer<T, V> {
    static_assert(StreamWriteable<T> && Stringable<T>, "abi::Writer<T, V>: can not write non-specified fundamental type");

    static void write(QDataStream& out, const T& obj) {
        out << obj;
    }

    static void write(StringListCursor& out, const T& obj) {
        if constexpr (std::is_arithmetic_v<T>) {
            out.append(QString::number(obj));
        }
        else if constexpr (StringType<T>) {
            out.append(QString{obj});
        }

        qWarning("%s", QString::asprintf("abi::Writer<%s, %s>: cannot write non-specified fundamental type",
                                         typeid(T).name(),
                                         typeid(V).name()).toUtf8().constData());
    }
};

/**
 * @brief The Reader class
 */
template <FundamentalType T, Version V>
struct Reader<T, V> {
    static_assert(StreamReadable<T>, "Reader<Fundamental T, V>:: can not read non-specified fundamental type");

    static void read(QDataStream& in, T& obj) {
        in >> obj;
    }

    static void read(const StringListCursor& in, T& obj) {
        if(in.empty()){
            qWarning("abi::Reader<FundamentalType T, V>: was given empti string list");
            return;
        }

        bool ok = true;
        if constexpr (std::is_integral_v<T>) {
            obj = static_cast<T>(in.at(0).toLongLong(&ok));
        } else if constexpr (std::is_floating_point_v<T>) {
            obj = static_cast<T>(in.at(0).toDouble(&ok));
        } else if constexpr (StringType<T>){
            obj = static_cast<T>(in.at(0).toStdString().c_str());
        }

        if (!ok) {
            qWarning() << "abi::Reader<FundamentalType T, V>: failed to convert string to number";
        }

        qWarning("%s", QString::asprintf("abi::Read<%s, %s>: cannot read non-specified fundamental type",
                                         typeid(T).name(),
                                         typeid(V).name()).toUtf8().constData());
    }
};

/**
 * @brief write
 * @param out
 * @param obj
 */
template <utils::GameEntity T, abi::Version V>
void write(QDataStream& out, const T& obj) {
    using base_t = typename T::base_t;
#ifdef POST_ORDER
    if constexpr (!std::is_same_v<base_t, void>) {
        write<base_t, V>(out, static_cast<const base_t&>(obj));
    }

    Writer<T, V>::write(out, obj);
#else
    Writer<T, V>::write(out, obj);

    if constexpr (!std::is_same_v<base_t, void>) {
        write<base_t, V>(out, static_cast<const base_t&>(obj));
    }
#endif
}

/**
 * @brief write
 * @param out
 * @param obj
 */
template <utils::GameEntity T, abi::Version V>
void write(StringListCursor& out, const T& obj) {
    using base_t = typename T::base_t;
#ifdef POST_ORDER
    if constexpr (!std::is_same_v<base_t, void>) {
        write<base_t, V>(out, static_cast<const base_t&>(obj));
    }

    Writer<T, V>::write(out, obj);
#else
    Writer<T, V>::write(out, obj);

    if constexpr (!std::is_same_v<base_t, void>) {
        write<base_t, V>(out, static_cast<const base_t&>(obj));
    }
#endif
}

/**
 * @brief read
 * @param in
 * @param obj
 */
template <utils::GameEntity T, abi::Version V>
void read(QDataStream& in, T& obj) {
    using base_t = typename T::base_t;
#ifdef POST_ORDER
    if constexpr (!std::is_same_v<base_t, void>) {
        read<base_t, V>(in, static_cast<base_t&>(obj));
    }

    Reader<T, V>::read(in, obj);
#else
    Reader<T, V>::read(in, obj);

    if constexpr (!std::is_same_v<base_t, void>) {
        read<base_t, V>(in, static_cast<base_t&>(obj));
    }
#endif
}

/**
 * @brief read
 * @param in
 * @param obj
 */
template <utils::GameEntity T, abi::Version V>
void read(StringListCursor& in, T& obj) {
    using base_t = typename T::base_t;
#ifdef POST_ORDER
    if constexpr (!std::is_same_v<base_t, void>) {
        read<base_t, V>(in, static_cast<base_t&>(obj));
    }

    Reader<T, V>::read(in, obj);
#else
    Reader<T, V>::read(in, obj);

    if constexpr (!std::is_same_v<base_t, void>) {
        read<base_t, V>(in, static_cast<base_t&>(obj));
    }
#endif
}

};  // namespace abi

#endif // READWRITE_H
