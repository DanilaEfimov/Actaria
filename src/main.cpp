#include <QApplication>
#include "Entities/dialognode.h"
#include "Entities/context.h"
#include "variables"
#include "characters"
#include "Entities/Operators/contextalgebra.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DialogNode node;
    Context context;

    ContextAlgebra ca = ContextAlgebra::XOr;

    AlgebraExpression* aexpr;

    qDebug() << static_cast<int>(ca);
    qDebug() << node.hash();        //  8336160681457226977
    qDebug() << context.hash();     //  7196818660407558044

    return a.exec();
}
