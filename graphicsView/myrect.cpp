#include "myrect.h"
#include "myTransform.h"
#include "geometry.h"
myRect::myRect()
    :myItem()
{

}

void myRect::reSetShape(QList<QPointF> *points, int index, double rotate)
{
    QPointF actionP = points->at(index);
    QPointF lastP = points->at((index+3)%4);
    QPointF opposetP = points->at((index+2)%4);
    QPointF nextP  = points->at((index+1)%4);

    double lineVectorY[3] = {0,1,0};//x轴方向向量
    double lineVectorX[3] = {1,0,0};//x轴方向向量

    myTransform trans;
    trans.rotate(rotate);//旋转向量以适应矩形角度
    double *TX = trans.transForm(lineVectorX);//旋转后X轴向量
    double *TY = trans.transForm(lineVectorY);//旋转后Y轴向量

    double* lineATX = getLineFromVector(TX,actionP);
    double* lineATY = getLineFromVector(TY,actionP);

    double* lineOPX = getLineFromVector(TX,opposetP);
    double* lineOPY = getLineFromVector(TY,opposetP);

    double* next = VectorOuter(lineOPY,lineATX);
    double* last = VectorOuter(lineATY,lineOPX);

    nextP = QPointF(next[0]/next[2],next[1]/next[2]);
    lastP = QPointF(last[0]/last[2],last[1]/last[2]);

    points->remove((index+1)%4);
    points->insert((index+1)%4,nextP);
    points->remove((index+3)%4);
    points->insert((index+3)%4,lastP);

    delete[] TX;
    delete[] TY;
    delete[] lineATX;
    delete[] lineATY;
    delete[] lineOPX;
    delete[] lineOPY;
    delete[] next;
    delete[] last;

    refresh(points);
}
