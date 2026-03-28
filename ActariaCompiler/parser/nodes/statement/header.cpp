#include "header.h"


/**
 * @brief Header::Header
 * @param head
 * @param params
 */
Header::Header(Keyword head, QVector<expr>&& params)
    : Node(), head(head), params(std::move(params))
{}

/**
 * @brief Header::getHead
 * @return
 */
QString Header::getHead() const
{
    return this->head.get();
}

/**
 * @brief Header::getParams
 * @return
 */
const QVector<Header::expr> &Header::getParams() const
{
    return this->params;
}
