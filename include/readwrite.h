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

/// fundamental types specification for read-write interface
template <typename T, Version V = EngineInfo::defaultVersion>
    requires std::is_fundamental_v<T>
void write(QDataStream& out, const T& obj) {
    out << obj;
}

template <typename T, Version V = EngineInfo::defaultVersion>
    requires std::is_fundamental_v<T>
void read(QDataStream& in, T& obj) {
    in >> obj;
}

/// entity types  declaration for read-write interface
template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
void write(QDataStream& out, const T& obj);

template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
void read(QDataStream& in, T& obj);

template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
void write(QStringList& out, const T& obj);

template <utils::GameEntity T, Version V = EngineInfo::defaultVersion>
void read(QStringList& in, T& obj);

};  // namespace abi

#endif // READWRITE_H
