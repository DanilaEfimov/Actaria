#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "entity.h"
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
[[nodiscard]] const T& randomElement(const QSet<T>& set)
{
    if (set.isEmpty()) {
        throw std::runtime_error("Cannot choose random element from empty QSet");
    }

    int index = QRandomGenerator::global()->bounded(set.size());
    auto it = set.constBegin();
    std::advance(it, index);
    return *it;
}

#endif // TESTUTILS_H
