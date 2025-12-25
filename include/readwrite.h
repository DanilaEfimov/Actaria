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

template <typename T, Version V = EngineInfo::defaultVersion>
struct measure_traits {
    static constexpr bool is_fixed = std::is_fundamental<T>::value;
    static constexpr int minimum_bytes = sizeof(T);
    static constexpr int maximum_bytes = sizeof(T);
};

template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
struct entity_measure_traits : public measure_traits<T, V> {
    static constexpr int minimum_words = 1;
    static constexpr int maximum_words = unlimited;
};

template <typename T, Version V = EngineInfo::defaultVersion>
struct Writer {
    static_assert(sizeof(T) == 0, "abi::Writer<T, V>: specialization required");

    static void write(QDataStream&, const T&);
    static void write(QStringList&, const T&);
};

template <typename T, Version V = EngineInfo::defaultVersion>
struct Reader {
    static_assert(sizeof(T) == 0, "abi::Reader<T, V>: specialization required");

    static void read(QDataStream&, T&);
    static void read(const QStringList&, T&);
};

/// fundamental types specification for read-write interface
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

/// entity-based types declarations for read-write interface
template <utils::GameEntity T, Version V>
struct Writer<T, V> {
    static_assert(sizeof(T) == 0, "abi::Writer<utils::GameEntity T, V>: specialization required");

    static void write(QDataStream&, const T&);
    static void write(QStringList&, const T&);
};

template <utils::GameEntity T, Version V>
struct Reader<T, V> {
    static_assert(sizeof(T) == 0, "abi::Reader<utils::GameEntity T, V>: specialization required");

    static void read(QDataStream&, const T&);
    static void read(const QStringList&, const T&);
};

};  // namespace abi

#endif // READWRITE_H
