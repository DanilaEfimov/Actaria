#include "utils.h"


/**
 * @brief Utils::toString
 * @param category
 * @return
 */
QString Utils::toString(TokenCategory category)
{
    switch (category)
    {
        case TokenCategory::Identifier: return "Identifier";
        case TokenCategory::Keyword: return "Keyword";
        case TokenCategory::TextLiteral: return "TextLiteral";
        case TokenCategory::NumberLiteral: return "NumberLiteral";
        case TokenCategory::TriggerLiteral: return "TriggerLiteral";
        case TokenCategory::SingleComment: return "SingleComment";
        case TokenCategory::Arithmetic: return "Arithmetic";
        case TokenCategory::Separator: return "Separator";
        case TokenCategory::LBrace: return "LBrace";
        case TokenCategory::RBrace: return "RBrace";
        case TokenCategory::Quote: return "Quote";
        case TokenCategory::Colon: return "Colon";
        case TokenCategory::Eof: return "Eof";
    default:
        return "Unknown";
    }
}
