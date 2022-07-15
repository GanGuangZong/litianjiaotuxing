#include "myparallelogram.h"
#include "geometry.h"
#include "myTransform.h"

myParallelogram::myParallelogram()
{

}

void myParallelogram::reSetShape(QList<QPointF> *points, int index, double rotate)
{
    Q_UNUSED(rotate)
    QPointF actionP = points->at(index);
    //QPointF opposetP = points->at((index+2)%4);
    QPointF lastP = points->at((index+3)%4);
    QPointF nextP  = points->at((index+1)%4);

    double* middleP = middlePoint(nextP,lastP);
    QPointF middle(middleP[0]/middleP[2],middleP[1]/middleP[2]);
    myTransform trans;
    trans.Translate(-middle.x(),-middle.y());
    trans.rotate(PI);
    trans.Translate(middle.x(),middle.y());
    QPointF opposetP = trans.transForm(actionP);

    points->remove((index+2)%4);
    points->insert((index+2)%4,opposetP);

    delete [] middleP;

    refresh(points);
}
