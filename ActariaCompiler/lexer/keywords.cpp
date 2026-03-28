#include "keywords.h"

QSet<QString> KeyWords::typeNames = {
    "text",         // string type name
    "number",       // integer type name
    "trigger",      // boolean type name
};

QSet<QString> KeyWords::keywords = QSet<QString>({
    "Scene",        // Scene definition keyword
    "Character",    // Character definition keyword
    "setEvent",     // mark handler definition keyword
    "import",       // names from file using keyword
    "mark",         // dialog node definition keyword
    "if",           // condition operator keyword
    "for",          // cycle operator keyword
    "import",       // symbol using keyword
    "jmp",          // built-in operator for event handlers
}).unite(KeyWords::typeNames);


/**
 * @brief KeyWords::contains
 * @param word
 * @return
 */
bool KeyWords::contains(const QString &word)
{
    return KeyWords::keywords.contains(word);
}

/**
 * @brief KeyWords::isTypeName
 * @param word
 * @return
 */
bool KeyWords::isTypeName(const QString &word)
{
    return KeyWords::typeNames.contains(word);
}
