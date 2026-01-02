#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "variables"
#include <QString>
#include <QRandomGenerator64>

namespace {
    QString sanitize(QString&& s)
    {
        QString result = s;
        for (QChar ch : QString(EngineInfo::separator)) {
            result.remove(ch);
        }
        return result;
    }
};

/**
 * @brief randomString
 * @param length
 * @return random generated QString of length 'length'
 * without chars, which contained in Entity::separator
 */
[[nodiscard]] inline QString randomString(int length) noexcept
{
    static const QString chars = sanitize("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:',.<>/?");
    QString result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(chars.size());
        result.append(chars.at(index));
    }
    return result;
}

/**
 * @brief randomElement
 * @param set
 * @return a random element from QSet
 */
template<typename T>
[[nodiscard]] inline const T& randomElement(const QSet<T>& set)
{
    if (set.isEmpty()) {
        throw std::runtime_error("Cannot choose random element from empty QSet");
    }

    int index = QRandomGenerator::global()->bounded(set.size());
    auto it = set.constBegin();
    std::advance(it, index);
    return *it;
}

#ifdef ACTARIA_TEST
#include <random>
#include <type_traits>

/**
 * @brief random_value
 * @return
 */
template<typename T>
inline T random_value(){
    static_assert(std::is_trivially_copyable_v<T>,
                  "random_value<T>: T must be trivially copyable");

    union u {
        T value;
        std::byte bytes[sizeof(T)];
    } data;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for (auto& b : data.bytes)
        b = static_cast<std::byte>(dist(gen));

    return data.value;
}

/**
 * @brief random_variable
 * @return
 */
inline std::unique_ptr<ContextVar> random_variable() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 2);

    int type = dist(gen);

    QString randomName = QString("var_%1").arg(random_value<uint32_t>());

    switch (type) {
    case 0: // Counter
        return std::make_unique<Counter>(
            random_value<Counter::value_type>(),
            randomName
            );

    case 1: // Trigger
        return std::make_unique<Trigger>(
            static_cast<Trigger::value_type>(random_value<uint8_t>() & 1),
            randomName
            );

    case 2: // NameVar
        return std::make_unique<NameVar>(
            QString::number(random_value<uint32_t>()),
            randomName
            );

    default:
        return nullptr;
    }
}
#endif

#endif // TESTUTILS_H
