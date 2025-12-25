/**
 * engineinfo.h
 * Defines general compile-time engine metadata
 */

#ifndef ENGINEINFO_H
#define ENGINEINFO_H

#include <QDataStream>

namespace abi {

enum Version {
    Act_1_0,
};

//TODO: AbiOrderPolicy
enum class AbiOrder {
    Pre,
    Post
};

struct EngineInfo {
    // abi section
    static constexpr Version defaultVersion = Version::Act_1_0;
    static constexpr AbiOrder defaultOrder = AbiOrder::Post;
    static constexpr int endian = QDataStream::BigEndian;

    // serialize section
    static constexpr const char* separator = "::";
};

};  // namespace abi

#endif // ENGINEINFO_H
