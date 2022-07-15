#include "myrhombus.h"
#include "myTransform.h"
#include "geometry.h"

myRhombus::myRhombus()
{

}

void myRhombus::reSetShape(QList<QPointF> *points, int index, double rotate)
{
    Q_UNUSED(rotate)
    QPointF actionP = points->at(index);
    QPointF lastP = points->at((index+3)%4);
    QPointF opposetP = points->at((index+2)%4);
    QPointF nextP  = points->at((index+1)%4);

    double* diagonal1 = getLine(lastP,nextP);
    myTransform trans;
    trans.rotate(PI/2);
    double* diagonal2 = trans.transForm(diagonal1);
    double* normalPoint = normalFoot(diagonal2,actionP);
    actionP = QPoint(normalPoint[0]/normalPoint[2],normalPoint[1]/normalPoint[2]);
    myTransform trans2;
    trans2.rotate(PI);
    opposetP = trans2.transForm(actionP);

    points->remove(index);
    points->insert(index,actionP);
    points->remove((index+2)%4);
    points->insert((index+2)%4,opposetP);

    delete[] diagonal1;
    delete[] diagonal2;
    delete[] normalPoint;

    refresh(points);
}
