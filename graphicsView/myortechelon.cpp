#include "myortechelon.h"
#include "geometry.h"
#include "myTransform.h"

myOrtEchelon::myOrtEchelon()
{

}

void myOrtEchelon::reSetShape(QList<QPointF> *points, int index, double rotate)
{
    QPointF P1 = points->at(0);
    QPointF P3 = points->at(2);
    QPointF P4 = points->at(3);
    QPointF P2  = points->at(1);

    double lineVectorX[3] = {1,0,0};
    double lineVectorY[3] = {0,1,0};
    myTransform trans;
    trans.rotate(rotate);//旋转向量以适应矩形角度
    double *TX = trans.transForm(lineVectorX);//旋转后X轴向量
    double *TY = trans.transForm(lineVectorY);//旋转后Y轴向量

    if(index == 0)
    {
        double* bottomLine = getLineFromVector(TX,P3);
        double* leftLine = getLineFromVector(TY,P1);
        double* bottomLeftP = VectorOuter(bottomLine,leftLine);
        P2 = QPointF(bottomLeftP[0]/bottomLeftP[2],bottomLeftP[1]/bottomLeftP[2]);

        double* p4Line = getLineFromVector(TY,P4);
        int p1Position = positionPointAndLine(P1,p4Line);
        double* p3Line = getLineFromVector(TY,P3);
        int p2Position = positionPointAndLine(P2,p3Line);

        if( p1Position >= 0 && p2Position < 0 )
        {
            double* foot = normalFoot(p4Line,P1);
            P1 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);
            P4 = P1;
            double* bottomLine = getLineFromVector(TX,P3);
            double* leftLine = getLineFromVector(TY,P1);
            double* bottomLeftP = VectorOuter(bottomLine,leftLine);
            P2 = QPointF(bottomLeftP[0]/bottomLeftP[2],bottomLeftP[1]/bottomLeftP[2]);
            points->remove(1);
            points->insert(1,P2);
            points->remove(0);
            points->insert(0,P1);
            points->remove(3);
            points->insert(3,P4);

            delete []  foot;
            delete []  bottomLine;
            delete []  leftLine;
            delete []  bottomLeftP;
            return;
        }


        if( p2Position >= 0 && p1Position < 0 )
        {
            double* foot = normalFoot(p3Line,P2);
            P2 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);

            double* topLine = getLineFromVector(TX,P1);
            double* p3Line = getLineFromVector(TY,P3);
            double* topLeftP = VectorOuter(topLine,p3Line);
            P1 = QPointF(topLeftP[0]/topLeftP[2],topLeftP[1]/topLeftP[2]);

            double* topRigetP = VectorOuter(topLine,p4Line);
            P4 = QPointF(topRigetP[0]/topRigetP[2],topRigetP[1]/topRigetP[2]);

            points->remove(1);
            points->insert(1,P2);
            points->remove(0);
            points->insert(0,P1);
            points->remove(3);
            points->insert(3,P4);
            return;
        }

        if( p2Position >= 0 && p1Position >= 0 )
        {
            int p3Postion = positionPointAndLine(P3,p4Line);
            if( p3Postion >= 0 )
            {
                double* foot1 = normalFoot(p4Line,P1);
                P1 = QPointF(foot1[0]/foot1[2],foot1[1]/foot1[2]);
                P4 = P1;
                double* foot2 = normalFoot(p4Line,P2);
                P2 = QPointF(foot2[0]/foot2[2],foot2[1]/foot2[2]);

                points->remove(1);
                points->insert(1,P2);
                points->remove(0);
                points->insert(0,P1);
                points->remove(3);
                points->insert(3,P4);

                delete [] foot1;
                delete [] foot2;
            }
            else
            {
                double* foot1 = normalFoot(p3Line,P1);
                P1 = QPointF(foot1[0]/foot1[2],foot1[1]/foot1[2]);
                P2 = P3;
                double* topLine = getLineFromVector(TX,P1);
                double* topRightP = VectorOuter(topLine,p4Line);
                P4 = QPointF(topRightP[0]/topRightP[2],topRightP[1]/topRightP[2]);

                points->remove(1);
                points->insert(1,P2);
                points->remove(0);
                points->insert(0,P1);
                points->remove(3);
                points->insert(3,P4);

                delete [] foot1;
                delete [] topLine;
                delete [] topRightP;
            }

            return;
        }

        double* rightLine = getLineFromVector(TY,P4);
        double* topLine = getLineFromVector(TX,P1);
        double* topRightP = VectorOuter(rightLine,topLine);
        P4 = QPointF(topRightP[0]/topRightP[2],topRightP[1]/topRightP[2]);

        points->remove(1);
        points->insert(1,P2);
        points->remove(3);
        points->insert(3,P4);

        delete [] p3Line;
        delete [] rightLine;
        delete [] topLine;
        delete [] topRightP;
        delete [] bottomLine;
        delete [] leftLine;
        delete [] bottomLeftP;
    }
    else if(index == 1)
    {
        double* topLine = getLineFromVector(TX,P4);
        double* leftLine = getLineFromVector(TY,P2);
        double* bottomLeftP = VectorOuter(topLine,leftLine);
        P1 = QPointF(bottomLeftP[0]/bottomLeftP[2],bottomLeftP[1]/bottomLeftP[2]);

        double* p4Line = getLineFromVector(TY,P4);
        int p1Position = positionPointAndLine(P1,p4Line);
        double* p3Line = getLineFromVector(TY,P3);
        int p2Position = positionPointAndLine(P2,p3Line);

        if( p1Position >= 0 && p2Position < 0 )
        {
            double* foot = normalFoot(p4Line,P2);
            P2 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);
            P1 = P4;

            double* bottomLine = getLineFromVector(TX,P2);
            double* rightLine = getLineFromVector(TY,P3);
            double* bottomRightP = VectorOuter(bottomLine,rightLine);
            P3 = QPointF(bottomRightP[0]/bottomRightP[2],bottomRightP[1]/bottomRightP[2]);

            points->remove(1);
            points->insert(1,P2);
            points->remove(0);
            points->insert(0,P1);
            points->remove(2);
            points->insert(2,P3);

            delete []  foot;
            delete []  bottomLine;
            delete []  rightLine;
            delete []  bottomRightP;
            return;
        }

        if( p2Position >= 0 && p1Position < 0 )
        {
            double* foot = normalFoot(p3Line,P2);
            P2 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);

            double* topLine = getLineFromVector(TX,P4);
            double* p3Line = getLineFromVector(TY,P3);
            double* topLeftP = VectorOuter(topLine,p3Line);
            P1 = QPointF(topLeftP[0]/topLeftP[2],topLeftP[1]/topLeftP[2]);

            P3 = P2;

            points->remove(1);
            points->insert(1,P2);
            points->remove(0);
            points->insert(0,P1);
            points->remove(2);
            points->insert(2,P3);
            return;
        }

        if( p2Position >= 0 && p1Position >= 0 )
        {
            int p3Postion = positionPointAndLine(P3,p4Line);
            if( p3Postion >= 0 )
            {
                P1 = P4;
                double* foot2 = normalFoot(p4Line,P2);
                P2 = QPointF(foot2[0]/foot2[2],foot2[1]/foot2[2]);

                double* bottomLine = getLineFromVector(TX,P2);
                double* rightLine = getLineFromVector(TY,P3);
                double* bottomRightP = VectorOuter(bottomLine,rightLine);
                P3 = QPointF(bottomRightP[0]/bottomRightP[2],bottomRightP[1]/bottomRightP[2]);

                points->remove(1);
                points->insert(1,P2);
                points->remove(0);
                points->insert(0,P1);
                points->remove(2);
                points->insert(2,P3);

                delete [] foot2;
            }
            else
            {
                double* foot1 = normalFoot(p3Line,P2);
                P2 = QPointF(foot1[0]/foot1[2],foot1[1]/foot1[2]);

                P3 = P2;

                double* topLine = getLineFromVector(TX,P4);
                double* leftLine = getLineFromVector(TY,P2);
                double* topLeftP = VectorOuter(topLine,leftLine);
                P1 = QPointF(topLeftP[0]/topLeftP[2],topLeftP[1]/topLeftP[2]);

                points->remove(1);
                points->insert(1,P2);
                points->remove(0);
                points->insert(0,P1);
                points->remove(2);
                points->insert(2,P3);

                delete [] foot1;
                delete [] topLine;
                delete [] topLeftP;
                delete [] leftLine;
            }

            return;
        }

        double* rightLine = getLineFromVector(TY,P3);
        double* bottomP2Line = getLineFromVector(TX,P2);
        double* bottomRight = VectorOuter(rightLine,bottomP2Line);
        P3 = QPointF(bottomRight[0]/bottomRight[2],bottomRight[1]/bottomRight[2]);

        points->remove(0);
        points->insert(0,P1);
        points->remove(2);
        points->insert(2,P3);

        delete [] p3Line;
        delete [] rightLine;
        delete [] bottomP2Line;
        delete [] bottomRight;
        delete [] topLine;
        delete [] leftLine;
        delete [] bottomLeftP;
    }
    else if(index == 2)
    {
        double* P1YLine = getLineFromVector(TY,P1);
        int P3Position = positionPointAndLine(P3,P1YLine);
        if( P3Position <= 0 )
        {
            double* foot = normalFoot(P1YLine,P3);
            P3 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);
            P2 = P3;
            points->remove(1);
            points->insert(1,P2);
            points->remove(2);
            points->insert(2,P3);
            return;
        }
        double* p1LeftLine = getLineFromVector(TY,P1);
        double* p3TopLine = getLineFromVector(TX,P3);
        double* bottomLeft = VectorOuter(p1LeftLine,p3TopLine);
        P2 = QPointF(bottomLeft[0]/bottomLeft[2],bottomLeft[1]/bottomLeft[2]);

        points->remove(1);
        points->insert(1,P2);
    }
    else
    {
        double* P1YLine = getLineFromVector(TY,P1);
        int P4Position = positionPointAndLine(P4,P1YLine);
        if( P4Position <= 0 )
        {
            double* foot = normalFoot(P1YLine,P4);
            P4 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);
            P1 = P4;
            points->remove(0);
            points->insert(0,P1);
            points->remove(3);
            points->insert(3,P4);
            return;
        }
        double* p2LeftLine = getLineFromVector(TY,P2);
        double* p4TopLine = getLineFromVector(TX,P4);
        double* topLeftP = VectorOuter(p2LeftLine,p4TopLine);
        P1 = QPointF(topLeftP[0]/topLeftP[2],topLeftP[1]/topLeftP[2]);

        points->remove(0);
        points->insert(0,P1);
    }

    delete [] TX;
    delete [] TY;

    refresh(points);
}
