#include "stringlistcursor.h"
#include "Logging/logcore.h"

#include <algorithm>


/**
 * @brief StringListCursor::StringListCursor
 * @param from
 */
StringListCursor::StringListCursor(const QStringList& target, qsizetype from)
    : words(target.mid(from)), pointer()
{}

/**
 * @brief StringListCursor::StringListCursor
 */
StringListCursor::StringListCursor(QStringList&& target)
    : words(std::move(target)), pointer()
{}

/**
 * @brief StringListCursor::hasNext
 * @return true if pointer doesn't look at the end
 */
bool StringListCursor::hasNext() const noexcept
{
    return this->pointer < this->words.size();
}

/**
 * @brief StringListCursor::peek
 * @return actual cursoring string
 */
QString StringListCursor::peek() const
{
    return hasNext() ? words.at(pointer) : QString{};
}

/**
 * @brief StringListCursor::next
 * @return next string if it's exists
 */
QString StringListCursor::next()
{
    return hasNext() ? words.at(++pointer) : QString{};
}

/**
 * @brief StringListCursor::remaining
 * @return count of not viewed strings
 */
qsizetype StringListCursor::remaining() const noexcept
{
    return std::max<qsizetype>(0, this->words.size() - this->pointer);
}

/**
 * @brief StringListCursor::size
 * @return actual size of this->words
 */
qsizetype StringListCursor::size() const noexcept
{
    return this->words.size();
}

/**
 * @brief StringListCursor::empty
 * @return true if this->words is empty
 */
bool StringListCursor::empty() const noexcept
{
    return this->words.empty();
}

/**
 * @brief StringListCursor::skip
 * @param count
 */
void StringListCursor::skip(qsizetype count)
{
    this->pointer = std::min(this->pointer + count, this->words.size());
}

/**
 * @brief StringListCursor::reset
 */
void StringListCursor::reset()  noexcept
{
    this->pointer = 0;
}

/**
 * @brief StringListCursor::position
 * @return actual position of cursor
 */
qsizetype StringListCursor::position() const noexcept
{
    return this->pointer;
}

/**
 * @brief StringListCursor::append
 * @param word
 */
void StringListCursor::append(QString&& word)
{
    this->words.append(std::move(word));
}

/**
 * @brief StringListCursor::append
 * @param words
 */
void StringListCursor::append(QStringList&& words)
{
    this->words.append(std::move(words));
}

/**
 * @brief StringListCursor::append
 * @param word
 */
void StringListCursor::append(const QString& word)
{
    this->words.append(word);
}

/**
 * @brief StringListCursor::append
 * @param words
 */
void StringListCursor::append(const QStringList& words)
{
    this->words.append(words);
}

/**
 * @brief StringListCursor::peekFirst
 * @return
 */
QString StringListCursor::peekFirst() const noexcept
{
    return !this->words.empty() ? this->words.constFirst() : QString{};
}

/**
 * @brief StringListCursor::peekLast
 * @return
 */
QString StringListCursor::peekLast() const noexcept
{
    return !this->words.empty() ? this->words.constLast() : QString{};
}

/**
 * @brief StringListCursor::at
 * @param idx
 * @return element at directed index
 */
const QString& StringListCursor::at(qsizetype idx) const noexcept
{
    return this->words.at(idx);
}

/**
 * @brief StringListCursor::clear
 */
void StringListCursor::clear() noexcept
{
    this->words.clear();
    this->pointer = 0;
}

/**
 * @brief StringListCursor::remove
 * @param idx
 */
void StringListCursor::remove(qsizetype idx) noexcept
{
    if(idx >= this->words.size()) {
        if (logCore().isDebugEnabled()) {
            qWarning(logCore) << "StringListCursor::remove: index out of range:" << idx;
        }
        return;
    }

    this->words.remove(idx);

    if(idx < this->pointer)
        this->pointer--;
}

/**
 * @brief StringListCursor::removeLast
 */
void StringListCursor::removeLast() noexcept
{
    if(this->words.empty()){
        if (logCore().isDebugEnabled()) {
            qWarning(logCore) << "StringListCursor::removeLast: list is empty";
        }
        return;
    }

    this->words.removeLast();
}

/**
 * @brief StringListCursor::removeFirst
 */
void StringListCursor::removeFirst() noexcept
{
    if(this->words.empty()){
        if (logCore().isDebugEnabled()) {
            qWarning(logCore) << "StringListCursor::removeFirst: list is empty";
        }
        return;
    }

    this->words.removeFirst();
    if (pointer > 0) --this->pointer;
}

/**
 * @brief StringListCursor::toList
 * @return copy of this->words
 */
QStringList StringListCursor::toList() const
{
    return this->words;
}

/**
 * @brief StringListCursor::list
 * @return this->words reference
 */
const QStringList& StringListCursor::list() const noexcept
{
    return this->words;
}
