/**
 * engineinfo.h
 * Defines general compile-time engine metadata
 */

#ifndef ENGINEINFO_H
#define ENGINEINFO_H

namespace abi {

enum Version {
    Act_1_0,
};

struct EngineInfo {
    static constexpr Version defaultVersion = Version::Act_1_0;
};

};  // namespace abi

#endif // ENGINEINFO_H
