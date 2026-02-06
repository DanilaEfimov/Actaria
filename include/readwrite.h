/**
 * @file readwrite.h
 * here declared interface of reading and writing
 * engine entities as byte array and string
*/

#ifndef READWRITE_H
#define READWRITE_H

#include "common.h"
#include "engineinfo.h"
#include "stringlistcursor.h"
#include "Logging/logcore.h"

#include <type_traits>
#include <QByteArray>
#include <QDataStream>
#include <QStringList>

#ifdef ACTARIA_TEST
#define ENGINE_TEST friend class EngineTest;
#else
#define ENGINE_TEST
#endif

/**
 * @macro ACT_SERIALIZABLE
 * Marks a class as serializable in the ABI system.
 *
 * Usage:
 *      class MyClass {
 *          ACT_SERIALIZABLE
 *          ...
 *      };
 *
 * This macro declares friendship with the abi::Writer and abi::Reader
 * templates for all versions, allowing serialization and deserialization
 * of the class without exposing private members.
 */
#define ACT_SERIALIZABLE \
    ENGINE_TEST \
    template <utils::GameEntity T, abi::Version V> \
    friend struct abi::entity_traits; \
    template <typename T, abi::Version V> \
    friend struct abi::Writer; \
    template <typename T, abi::Version V> \
    friend struct abi::Reader; \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::write(DataStreamCursor&, const T&); \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::write(StringListCursor&, const T&); \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::read(DataStreamCursor&, T&); \
    template <utils::GameEntity T, abi::Version V> \
    friend void abi::read(StringListCursor&, T&);

/**
 * @macro SPECIFICATION_REQUIRED
 * Makes a template unit is required for specialization
 *
 * Usage:
 *      template<...>
 *      class/signature MyTemplateUnit {
 *
 *      SPECIFICATION_REQUIRED
 *      ...
 *
 *      }
 *
 * Artificial reflection assert
 * ISO C++ forbids in-class initialization of non-const static member
 * 'abi::Writer<T, V>::require'
 */
#define SPECIFICATION_REQUIRED \
static auto require = []() { \
    qDebug() << "T: " << typeid(T).name() << ", V: " << typeid(V).hash_code(); \
    return typeid(T).hash_code(); \
}();

class DataStreamCursor;

namespace abi {

static constexpr int unlimited = -1;

/**
 * @brief The entity_traits class
 */
template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
struct entity_traits {

    SPECIFICATION_REQUIRED

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

    SPECIFICATION_REQUIRED

    static void write(DataStreamCursor&, const T&);
    static void write(StringListCursor&, const T&);
};

/**
 * @brief The Reader class
 * read methods returns offset of readed data
 */
template <typename T, Version V = EngineInfo::defaultVersion>
struct Reader {

    SPECIFICATION_REQUIRED

    static void read(DataStreamCursor&, T&);
    static void read(StringListCursor&, T&);
};


/**
 * @brief The Writer class
 */
template <FundamentalType T, Version V>
struct Writer<T, V> {
    static_assert(StreamWriteable<T> && Stringable<T>, "abi::Writer<T, V>: can not write non-specified fundamental type");

    static void write(DataStreamCursor& out, const T& obj) {
        out << obj;
    }

    static void write(StringListCursor& out, const T& obj) {
        if constexpr (std::is_arithmetic_v<T>) {
            out.append(QString::number(obj));
        }
        else if constexpr (StringType<T>) {
            out.append(QString{obj});
        }

        qWarning(logCore, "%s", QString::asprintf("abi::Writer<%s, %s>: cannot write non-specified fundamental type",
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

    static void read(DataStreamCursor& in, T& obj) {
        in >> obj;
    }

    static void read(StringListCursor& in, T& obj) {
        if(in.empty()){
            qWarning(logCore, "abi::Reader<FundamentalType T, V>: was given empty string list");
            return;
        }

        bool ok = true;
        if constexpr (std::is_integral_v<T>) {
            obj = static_cast<T>(in.next().toLongLong(&ok));
        } else if constexpr (std::is_floating_point_v<T>) {
            obj = static_cast<T>(in.next().toDouble(&ok));
        } else if constexpr (StringType<T>){
            obj = static_cast<T>(in.next());
        }

        if (!ok) {
            qWarning(logCore) << "abi::Reader<FundamentalType T, V>: failed to convert string to number";
        }

        qWarning(logCore, "%s", QString::asprintf("abi::Read<%s, %s>: cannot read non-specified fundamental type",
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
void write(DataStreamCursor& out, const T& obj) {
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
void read(DataStreamCursor& in, T& obj) {
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
