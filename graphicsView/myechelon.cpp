#include "myechelon.h"
#include "geometry.h"
#include "myTransform.h"

myEchelon::myEchelon()
{

}

void myEchelon::reSetShape(QList<QPointF> *points, int index, double rotate)
{
    QPointF actionP = points->at(index);
    QPointF opposetP = points->at((index+2)%4);
    QPointF lastP = points->at((index+3)%4);
    QPointF nextP  = points->at((index+1)%4);
    double lineVectorX[3] = {1,0,0};
    double lineVectorY[3] = {0,1,0};
    myTransform trans;
    trans.rotate(rotate);//旋转向量以适应矩形角度
    double *TX = trans.transForm(lineVectorX);//旋转后X轴向量
    double *TY = trans.transForm(lineVectorY);//旋转后Y轴向量
    if(index == 0)
    {
        double* nextLine = getLineFromVector(TY,nextP);
        int actionPositionOfNextLine = positionPointAndLine(actionP,nextLine);

        double* line = getLineFromVector(TY,lastP);
        int position  = positionPointAndLine(actionP,line);
        if( position >= 0 )
        {
            double* p = normalFoot(line,actionP);
            actionP = QPointF(p[0]/p[2],p[1]/p[2]);
            lastP = actionP;
        }
        else
        {

            if(actionPositionOfNextLine <= 0)//邻角是钝角
            {
                double* line1 = getLineFromVector(TY,actionP);
                double* line2 = getLineFromVector(TX,opposetP);
                double* px = VectorOuter(line1,line2);
                nextP = QPointF(px[0]/px[2],px[1]/px[2]);
                delete[] px;
                delete[] line1;
                delete[] line2;
            }

            double* line3 = getLineFromVector(TX,actionP);
            double* line4 = getLineFromVector(TY,lastP);
            double* px2 = VectorOuter(line3,line4);
            lastP = QPointF(px2[0]/px2[2],px2[1]/px2[2]);
            delete [] px2;
            delete [] line3;
            delete [] line4;
            delete [] line;
            delete [] nextLine;
        }
    }
    else if(index == 1)
    {
        double* lastLine = getLineFromVector(TY,lastP);
        int actionPositionOfLastLine = positionPointAndLine(actionP,lastLine);

        if( actionPositionOfLastLine >= 0 )//是钝角
        {
            double* line1 = getLineFromVector(TY,actionP);
            double* line2 = getLineFromVector(TX,opposetP);
            double* px = VectorOuter(line1,line2);
            lastP = QPointF(px[0]/px[2],px[1]/px[2]);

            double* line = getLineFromVector(TY,opposetP);
            int position  = positionPointAndLine(lastP,line);
            if( position >= 0 )
            {
                double* p = normalFoot(line,actionP);
                lastP = opposetP;
                actionP = QPointF(p[0]/p[2],p[1]/p[2]);
                double* lineN = getLineFromVector(TY,nextP);//过点nextP做垂直于底边的垂线点nextp在其上移动
                double* footN = normalFoot(lineN,nextP);
                nextP = QPointF(footN[0]/footN[2],footN[1]/footN[2]);
                delete [] lineN;
                delete [] footN;
                delete [] p;
            }

            delete [] px;
            delete [] line1;
            delete [] line2;
            delete [] line;
            delete [] lastLine;
        }

        double* line3 = getLineFromVector(TX,actionP);
        double* line4 = getLineFromVector(TY,nextP);
        double* px2 = VectorOuter(line3,line4);
        nextP = QPointF(px2[0]/px2[2],px2[1]/px2[2]);
        delete[] px2;
        delete[] line3;
        delete[] line4;
    }
    else if(index == 2)
    {

        double* nextLine = getLineFromVector(TY,nextP);
        int actionPositionOfLastLine = positionPointAndLine(actionP,nextLine);
        if(actionPositionOfLastLine <= 0)//钝角
        {
            double* line1 = getLineFromVector(TY,actionP);
            double* line2 = getLineFromVector(TX,opposetP);
            double* px = VectorOuter(line1,line2);
            nextP = QPointF(px[0]/px[2],px[1]/px[2]);

            double* line = getLineFromVector(TY,opposetP);
            int position  = positionPointAndLine(nextP,line);
            if( position <= 0 )
            {
                double* p = normalFoot(line,actionP);
                nextP = opposetP;
                actionP = QPointF(p[0]/p[2],p[1]/p[2]);
                double* lineL = getLineFromVector(TY,lastP);//过点lastP做垂直于底边的垂线点lastP在其上移动
                double* footL = normalFoot(lineL,lastP);
                lastP = QPointF(footL[0]/footL[2],footL[1]/footL[2]);
                delete [] lineL;
                delete [] footL;
            }

            delete[] px;
            delete[] line1;
            delete[] line2;
        }

        double* line3 = getLineFromVector(TX,actionP);
        double* line4 = getLineFromVector(TY,lastP);
        double* px2 = VectorOuter(line3,line4);
        lastP = QPointF(px2[0]/px2[2],px2[1]/px2[2]);
        delete[] px2;
        delete[] line3;
        delete[] line4;
        delete [] nextLine;
    }
    else if(index == 3)
    {

        double* lastLine = getLineFromVector(TY,lastP);
        int actionPositionOfLastLine = positionPointAndLine(actionP,lastLine);

        double* line = getLineFromVector(TY,nextP);
        int position  = positionPointAndLine(actionP,line);
        if( position <= 0 )
        {
            double* p = normalFoot(line,actionP);
            actionP = QPointF(p[0]/p[2],p[1]/p[2]);
            nextP = actionP;
            delete [] p;
        }
        else
        {
            if(actionPositionOfLastLine >= 0)//邻角是钝角
            {
                double* line1 = getLineFromVector(TY,actionP);
                double* line2 = getLineFromVector(TX,opposetP);
                double* px = VectorOuter(line1,line2);
                lastP = QPointF(px[0]/px[2],px[1]/px[2]);
                delete[] px;
                delete[] line1;
                delete[] line2;
            }

            double* line3 = getLineFromVector(TX,actionP);
            double* line4 = getLineFromVector(TY,nextP);
            double* px2 = VectorOuter(line3,line4);
            nextP = QPointF(px2[0]/px2[2],px2[1]/px2[2]);
            delete[] px2;
            delete[] line3;
            delete[] line4;
            delete [] line;
            delete [] lastLine;
        }
    }

    points->remove((index+3)%4);
    points->insert((index+3)%4,lastP);
    points->remove((index+1)%4);
    points->insert((index+1)%4,nextP);
    points->remove(index);
    points->insert(index,actionP);

    delete [] TX;
    delete [] TY;
    refresh(points);
}
