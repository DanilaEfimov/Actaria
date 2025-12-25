/**
 * readwrite.h
 * here declared interface of reading and writing
 * engine entities as byte array and string
*/

#ifndef READWRITE_H
#define READWRITE_H

#include "utils.h"
#include "engineinfo.h"
#include <type_traits>
#include <QByteArray>
#include <QDataStream>
#include <QStringList>


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

    static constexpr const char* name = "";
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
    static void write(QStringList&, const T&);
};

/**
 * @brief The Reader class
 */
template <typename T, Version V = EngineInfo::defaultVersion>
struct Reader {
    static_assert(sizeof(T) == 0, "abi::Reader<T, V>: specialization required");

    static void read(QDataStream&, T&);
    static void read(const QStringList&, T&);
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

    static void write(QStringList& out, const T& obj) {
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
    static void read(QDataStream& in, T& obj) {
        in >> obj;
    }

    static void read(const QStringList& in, T& obj) {
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

        qWarning("%s", QString::asprintf("abi::Read<%s, %s>: cannot write non-specified fundamental type",
                                         typeid(T).name(),
                                         typeid(V).name()).toUtf8().constData());
    }
};

/**
 * @brief The Writer class
 */
template <utils::GameEntity T, Version V>
struct Writer<T, V> {
    using base_t = typename T::base_t;

    static void write(QDataStream& in, const T& obj) {
        if(std::is_same_v<T, base_t>){
            return;
        }

        in.setByteOrder(static_cast<QDataStream::ByteOrder>(EngineInfo::endian));

        if constexpr (EngineInfo::defaultOrder == AbiOrder::Post) {
            in << obj.hexHeader();
            Writer<base_t, V>::write(in, static_cast<const base_t&>(obj));
        }
        else {
            Writer<base_t, V>::write(in, static_cast<const base_t&>(obj));
            in << obj.hexHeader();
        }
    }

    static void write(QStringList& in, const T& obj) {
        if(std::is_same_v<T, base_t>){
            return;
        }

        if constexpr (EngineInfo::defaultOrder == AbiOrder::Post) {
            in.append(obj.strHeader());
            Writer<base_t, V>::write(in, static_cast<const base_t&>(obj));
        }
        else {
            Writer<base_t, V>::write(in, static_cast<const base_t&>(obj));
            in.append(obj.strHeader());
        }
    }
};

/**
 * @brief The Reader class
 */
template <utils::GameEntity T, Version V>
struct Reader<T, V> {
    using base_t = typename T::base_t;

    static void read(QDataStream& in, T& obj) {
        if(std::is_same_v<T, base_t>){
            return;
        }

        in.setByteOrder(static_cast<QDataStream::ByteOrder>(EngineInfo::endian));

        if constexpr (EngineInfo::defaultOrder == AbiOrder::Post) {
            // [Derived][Base]
            obj.fromDump(in);
            Reader<base_t, V>::read(in, static_cast<base_t&>(obj));
        }
        else {
            // [Base][Derived]
            Reader<base_t, V>::read(in, static_cast<base_t&>(obj));
            obj.fromDump(in);
        }
    }

    static void read(const QStringList& in, T& obj) {
        if(std::is_same_v<T, base_t>){
            return;
        }

        if constexpr (EngineInfo::defaultOrder == AbiOrder::Post) {
            obj.readStrHeader(in);
            Reader<base_t, V>::read(in, static_cast<base_t&>(obj));
        }
        else {
            Reader<base_t, V>::read(in, static_cast<base_t&>(obj));
            obj.readStrHeader(in);
        }
    }
};

};  // namespace abi

#endif // READWRITE_H
