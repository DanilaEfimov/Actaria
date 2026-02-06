/**
 * @file engineinfo.h
 * Defines general compile-time engine metadata
 */

#ifndef ENGINEINFO_H
#define ENGINEINFO_H

#include "config.h"
#include <QDataStream>

namespace abi {

enum Version {
    Act_1_0,
};

struct EngineInfo {
    // abi section
    static constexpr Version defaultVersion = Version::Act_1_0;

    static constexpr QDataStream::ByteOrder endian =
    #if defined(BIG_ENDIAN)
        QDataStream::BigEndian;
    #else
        QDataStream::LittleEndian;
    #endif

    // serialize section
    static constexpr const char* separator = "::";
};

};  // namespace abi

#endif // ENGINEINFO_H
