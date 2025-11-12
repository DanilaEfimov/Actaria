#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <cstdint>
#include <concepts>
#include "Entities/entity.h"

template<typename T>
concept GameEntity = std::derived_from<T, Entity>;

inline constexpr uint64_t fnv1a_64(const char* str, size_t n, uint64_t hash = 14695981039346656037ULL) {
    return n == 0 ? hash : fnv1a_64(str + 1, n - 1, (hash ^ static_cast<uint8_t>(*str)) * 1099511628211ULL);
}

template<typename T1, typename T2>
    requires GameEntity<T1> && GameEntity<T2>
inline constexpr bool is_same_entity_types(const T1& first, const T2& second) noexcept {
    return first.hash() == second.hash();
}

inline constexpr size_t strlen_ct(const char* str) noexcept {
    if (!str) return 0;
    size_t len = 0;
    while(str[len] != '\0') ++len;
    return len;
}

inline constexpr std::byte bitmask(int pos) noexcept {
    return std::byte(1 << pos % 8);
}

inline constexpr std::byte resetbit(int pos) noexcept {
    return ~bitmask(pos);
}

#endif // UTILS_H
