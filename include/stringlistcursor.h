/**
 * @file stringlistcursor.h
 * here defined cursor-based wrapper for QStringList.
*/

#ifndef STRINGLISTCURSOR_H
#define STRINGLISTCURSOR_H

#include <QString>
#include <QStringList>
#ifdef ACTARIA_TEST
#include <QDebug>
#endif

class StringListCursor {
    QStringList words;
    qsizetype pointer = 0;

public:
    StringListCursor() = default;
    explicit StringListCursor(const QStringList&, qsizetype from = 0);
    explicit StringListCursor(QStringList&&);
    ~StringListCursor() = default;

    bool hasNext() const noexcept;
    QString peek() const;
    QString next();

    qsizetype remaining() const noexcept;
    qsizetype size() const noexcept;
    bool empty() const noexcept;

    void skip(qsizetype count = 1);
    void reset() noexcept;
    qsizetype position() const noexcept;

    // container ops
    void append(QString&& word);
    void append(QStringList&& words);
    void append(const QString& word);
    void append(const QStringList& words);

    QString peekFirst() const noexcept;
    QString peekLast() const noexcept;
    const QString& at(qsizetype idx) const noexcept;

    void clear() noexcept;
    void remove(qsizetype idx) noexcept;
    void removeLast() noexcept;
    void removeFirst() noexcept;

    QStringList toList() const;
    const QStringList& list() const noexcept;
};

#endif // STRINGLISTCURSOR_H
