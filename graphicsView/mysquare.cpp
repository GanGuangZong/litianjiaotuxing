#include "mysquare.h"
#include "geometry.h"
#include "myTransform.h"

mySquare::mySquare()
{

}

void mySquare::reSetShape(QList<QPointF> *points, int index, double rotate)
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

    myTransform trans1;
    trans1.rotate(PI/4);
    double* Line135V = trans1.transForm(TY);
    double* Line45V = trans1.transForm(TX);

    double* midYLine = getLineFromVector(TY,opposetP);
    double* midXLine = getLineFromVector(TX,opposetP);
    double* Line45 = getLineFromVector(Line45V,opposetP);
    double* Line135 = getLineFromVector(Line135V,opposetP);

    int position1 = positionPointAndLine(actionP,midYLine);
    int position2 = positionPointAndLine(actionP,midXLine);
    int position3 = positionPointAndLine(actionP,Line45);
    int position4 = positionPointAndLine(actionP,Line135);

    double* actionLine = nullptr;
    double* PX = nullptr;
    if( position1 >= 0 )
    {
        if( position2 >= 0 )//1
        {
            if( position3 < 0 )
            {
                actionLine = getLineFromVector(TX,actionP);
                PX = VectorOuter(actionLine,Line45);
            }
            else
            {
                actionLine = getLineFromVector(TY,actionP);
                PX = VectorOuter(actionLine,Line45);
            }
        }
        else//4
        {
            if( position4 >= 0 )
            {
                actionLine = getLineFromVector(TX,actionP);
                PX = VectorOuter(actionLine,Line135);
            }
            else
            {
                actionLine = getLineFromVector(TY,actionP);
                PX = VectorOuter(actionLine,Line135);
            }
        }
    }
    else
    {
        if( position2 >= 0 )//2
        {
            if( position4 >= 0 )
            {
                actionLine = getLineFromVector(TY,actionP);
                PX = VectorOuter(actionLine,Line135);
            }
            else
            {
                actionLine = getLineFromVector(TX,actionP);
                PX = VectorOuter(actionLine,Line135);
            }
        }
        else//3
        {
            if( position3 < 0 )
            {
                actionLine = getLineFromVector(TY,actionP);
                PX = VectorOuter(actionLine,Line45);
            }
            else
            {
                actionLine = getLineFromVector(TX,actionP);
                PX = VectorOuter(actionLine,Line45);
            }
        }
    }

    actionP = QPointF(PX[0]/PX[2],PX[1]/PX[2]);

    double* middleP = middlePoint(actionP,opposetP);
    QPoint midP(middleP[0]/middleP[2],middleP[1]/middleP[2]);

    myTransform trans3;
    trans3.Translate(-midP.x(),-midP.y());
    trans3.rotate(PI/2);
    trans3.Translate(midP.x(),midP.y());
    nextP = trans3.transForm(actionP);
    lastP = trans3.transForm(opposetP);

    points->remove(index);
    points->insert(index,actionP);
    points->remove((index+1)%4);
    points->insert((index+1)%4,nextP);
    points->remove((index+3)%4);
    points->insert((index+3)%4,lastP);

    refresh(points);
}
