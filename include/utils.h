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

inline constexpr const int sizetypeSize = sizeof(quint32);
inline constexpr const int minimumQStringSize = sizetypeSize;
inline constexpr const int minimumQVectorSize = sizetypeSize;
inline constexpr const int minimumQContainerSize = sizetypeSize;

inline size_t QStringHexSize(const QString& str) noexcept {
    return minimumQStringSize + str.size() * sizeof(QChar);
}

template<typename T>
concept StringType =
    std::same_as<T, QString> ||
    std::same_as<T, std::string> ||
    std::is_base_of_v<std::basic_string_view<char>, T>;

template<typename T>
concept FundamentalType = std::is_fundamental_v<T>;

template<typename T>
concept Stringable =
    std::is_arithmetic_v<T> ||
    std::convertible_to<T, std::basic_string_view<char>> ||
    std::convertible_to<T, std::string> ||
    std::convertible_to<T, QString>;

template<typename T>
concept StreamWriteable = requires(QDataStream& s, T const& t) {
    { s << t } -> std::same_as<QDataStream&>;
};

template<typename T>
concept StreamReadable = requires(QDataStream& s, T const& t) {
    { s >> t } -> std::same_as<QDataStream&>;
};

namespace utils {

using hash_type = uint64_t;

template<typename T>
concept GameEntity =
    std::derived_from<T, Entity> ||
    std::is_same_v<T, Entity>;

template<typename T>
concept ContextVariable = std::derived_from<T, ContextVar>;

inline constexpr size_t strlen_ct(const char* str) noexcept {
    if (!str) return 0;
    size_t len = 0;
    while(str[len] != '\0') ++len;
    return len;
}

inline constexpr hash_type fnv1a_64(const char* str) {
    return __fnv1a_64(str, strlen_ct(str));
}

template<GameEntity T>
inline size_t QVectorOfEntitiesHexSize(const QVector<T>& container) noexcept {
    if(container.empty()){
        return minimumQVectorSize;
    }
    return minimumQVectorSize + container.size() * container.at(0).size();
}

template<GameEntity T1, GameEntity T2>
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
