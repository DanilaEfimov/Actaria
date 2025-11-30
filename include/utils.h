#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <QDebug>

class Entity;
class ContextVar;

namespace {
    using hash_type = uint64_t;

    constexpr uint64_t defaultHash = 14695981039346656037ULL;

    constexpr hash_type __fnv1a_64(const char* str, size_t n, uint64_t hash = defaultHash) {
        return n == 0 ? hash : __fnv1a_64(str + 1, n - 1, (hash ^ static_cast<uint8_t>(*str)) * 1099511628211ULL);
    }
};

// quint32 contains length of string
inline constexpr const int minimumQStringSize = sizeof(quint32);

inline size_t QStringHexSize(const QString& str) noexcept {
    return minimumQStringSize + str.size() * sizeof(QChar);
}

namespace utils {

using hash_type = uint64_t;

template<typename T>
concept GameEntity = std::derived_from<T, Entity>;

template<typename T>
concept ContextVariable = std::derived_from<T, ContextVar> && GameEntity<T>;

inline constexpr size_t strlen_ct(const char* str) noexcept {
    if (!str) return 0;
    size_t len = 0;
    while(str[len] != '\0') ++len;
    return len;
}

inline constexpr hash_type fnv1a_64(const char* str) {
    return __fnv1a_64(str, strlen_ct(str));
}

template<typename T1, typename T2>
    requires GameEntity<T1> && GameEntity<T2>
inline constexpr bool is_same_entity_types(const T1& first, const T2& second) noexcept {
    return first.hash() == second.hash();
}

// abi stuff
inline constexpr std::byte bitmask(int pos) noexcept {
    return std::byte(1 << pos % 8);
}

inline constexpr std::byte resetbit(int pos) noexcept {
    return ~bitmask(pos);
}

}   // namespace utils
#endif // UTILS_H
