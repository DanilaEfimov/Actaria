#include "illegalsymbolerror.h"

IllegalSymbolError::IllegalSymbolError(int col, int line)
    : LexerError(QString("Illegal symbol at (")
                 + QString::number(line + 1)
                 + ", "
                 + QString::number(col + 1) + ")")
{}
