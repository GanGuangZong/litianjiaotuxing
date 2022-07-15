#include "myequalechelon.h"
#include "geometry.h"
#include "myTransform.h"

myEqualEchelon::myEqualEchelon()
{

}

void myEqualEchelon::reSetShape(QList<QPointF> *points, int index, double rotate)
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
        double* middleP = middlePoint(P2,P3);
        double* symmetryLine = getLineFromVector(TY,QPointF(middleP[0]/middleP[2],middleP[1]/middleP[2]));
        int position = positionPointAndLine(P1,symmetryLine);
        if(position >= 0)
        {
            double* foot = normalFoot(symmetryLine,P1);
            P1 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);
            P4 = P1;
            delete [] foot;
        }
        double* topLine = getLineFromVector(TX,P1);
        double* topLineCenter = VectorOuter(symmetryLine,topLine);
        QPointF TPC(topLineCenter[0]/topLineCenter[2],topLineCenter[1]/topLineCenter[2]);
        myTransform trans;
        trans.Translate(-TPC.x(),-TPC.y());
        trans.rotate(PI);
        trans.Translate(TPC.x(),TPC.y());
        P4 = trans.transForm(P1);


        points->remove(0);
        points->insert(0,P1);
        points->remove(3);
        points->insert(3,P4);

        delete [] topLine;
        delete [] topLineCenter;
        delete [] middleP;
        delete [] symmetryLine;
    }
    else if(index == 3)
    {
        double* middleP = middlePoint(P2,P3);
        double* symmetryLine = getLineFromVector(TY,QPointF(middleP[0]/middleP[2],middleP[1]/middleP[2]));
        int position = positionPointAndLine(P4,symmetryLine);
        if(position <= 0)
        {
            double* foot = normalFoot(symmetryLine,P4);
            P4 = QPointF(foot[0]/foot[2],foot[1]/foot[2]);
            P1 = P4;
            delete [] foot;
        }
        double* topLine = getLineFromVector(TX,P4);
        double* topLineCenter = VectorOuter(symmetryLine,topLine);
        QPointF TPC(topLineCenter[0]/topLineCenter[2],topLineCenter[1]/topLineCenter[2]);
        myTransform trans;
        trans.Translate(-TPC.x(),-TPC.y());
        trans.rotate(PI);
        trans.Translate(TPC.x(),TPC.y());
        P1 = trans.transForm(P4);


        points->remove(0);
        points->insert(0,P1);
        points->remove(3);
        points->insert(3,P4);

        delete [] topLine;
        delete [] topLineCenter;
        delete [] middleP;
        delete [] symmetryLine;
    }
    else if(index == 1)//完成
    {
        double* previousMiddleTopP = middlePoint(P1,P4);
        double* previousSymmetryLine = getLineFromVector(TY,QPointF(previousMiddleTopP[0]/previousMiddleTopP[2],previousMiddleTopP[1]/previousMiddleTopP[2]));
        double* previousBottomLine = getLineFromVector(TX,P3);
        double* previousMiddleBottomP = VectorOuter(previousSymmetryLine,previousBottomLine);
        QPointF PMiddBottomP(previousMiddleBottomP[0]/previousMiddleBottomP[2],previousMiddleBottomP[1]/previousMiddleBottomP[2]);

        //上一次的P3点，对称出上一次的p2点。新P2点向上一次底边做垂线，垂足与上一次P2点之差就是P1移动的方向向量
        myTransform trans;
        trans.Translate(-PMiddBottomP.x(),-PMiddBottomP.y());
        trans.rotate(PI);
        trans.Translate(PMiddBottomP.x(),PMiddBottomP.y());
        QPointF previousP2 = trans.transForm(P3);

        double* foot = normalFoot(previousBottomLine,P2);
        QPointF footP2(foot[0]/foot[2],foot[1]/foot[2]);
        myTransform trans2;
        trans2.Translate(footP2.x()-previousP2.x(),footP2.y()-previousP2.y());
        P1 = trans2.transForm(P1);

        double* P4YLine = getLineFromVector(TY,P4);
        int positionP1 = positionPointAndLine(P1,P4YLine);
        double* P3YLine = getLineFromVector(TY,P3);
        int positionP2 = positionPointAndLine(P2,P3YLine);

        if( positionP2 >= 0 && positionP1 < 0 )
        {
            double* symmetry = getLineFromVector(TY,P3);
            double* P2Foot = normalFoot(symmetry,P2);
            P2 = QPointF(P2Foot[0]/P2Foot[2],P2Foot[1]/P2Foot[2]);
            P3 = P2;

            double* topLine = getLineFromVector(TX,P4);
            double* topMiddleP = VectorOuter(topLine,symmetry);
            QPointF topMid(topMiddleP[0]/topMiddleP[2],topMiddleP[1]/topMiddleP[2]);
            myTransform trans;
            trans.Translate(-topMid.x(),-topMid.y());
            trans.rotate(PI);
            trans.Translate(topMid.x(),topMid.y());
            P1 = trans.transForm(P4);

            points->remove(0);
            points->insert(0,P1);
            points->remove(1);
            points->insert(1,P2);
            points->remove(2);
            points->insert(2,P3);
            return;
        }


        if( positionP1 >= 0 && positionP2 < 0 )
        {
            //P2相对称轴作垂线，垂足PP2。上一次P3向对称轴作垂线，垂足与pp2只差就是p3移动的方向向量。
            //计算出最新的p3后对称出要求的p2
            P1 = P4;
            double* symmetry = getLineFromVector(TY,P4);
            double* P2Foot = normalFoot(symmetry,P2);
            double* P3Foot = normalFoot(symmetry,P3);
            QPointF P2FootP(P2Foot[0]/P2Foot[2],P2Foot[1]/P2Foot[2]);
            QPointF P3FootP(P3Foot[0]/P3Foot[2],P3Foot[1]/P3Foot[2]);

            myTransform trans;
            trans.Translate(P2FootP.x()-P3FootP.x(),P2FootP.y()-P3FootP.y());
            P3 = trans.transForm(P3);

            double* bottomLine = getLineFromVector(TX,P2);
            double* bottomMiddP = VectorOuter(bottomLine,symmetry);
            QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
            myTransform trans2;
            trans2.Translate(-bottomMid.x(),-bottomMid.y());
            trans2.rotate(PI);
            trans2.Translate(bottomMid.x(),bottomMid.y());
            P2 = trans2.transForm(P3);

            points->remove(1);
            points->insert(1,P2);
            points->remove(2);
            points->insert(2,P3);
            points->remove(0);
            points->insert(0,P1);
            return;
        }

        if( positionP1 > 0 && positionP2 > 0 )
        {
            int p3Postion = positionPointAndLine(P3,P4YLine);
            if( p3Postion >= 0 )
            {
                //P2相对称轴作垂线，垂足PP2。上一次P3向对称轴作垂线，垂足与pp2只差就是p3移动的方向向量。
                //计算出最新的p3后对称出要求的p2
                P1 = P4;
                double* symmetry = getLineFromVector(TY,P4);
                double* P2Foot = normalFoot(symmetry,P2);
                double* P3Foot = normalFoot(symmetry,P3);
                QPointF P2FootP(P2Foot[0]/P2Foot[2],P2Foot[1]/P2Foot[2]);
                QPointF P3FootP(P3Foot[0]/P3Foot[2],P3Foot[1]/P3Foot[2]);

                myTransform trans;
                trans.Translate(P2FootP.x()-P3FootP.x(),P2FootP.y()-P3FootP.y());
                P3 = trans.transForm(P3);

                double* bottomLine = getLineFromVector(TX,P2);
                double* bottomMiddP = VectorOuter(bottomLine,symmetry);
                QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
                myTransform trans2;
                trans2.Translate(-bottomMid.x(),-bottomMid.y());
                trans2.rotate(PI);
                trans2.Translate(bottomMid.x(),bottomMid.y());
                P2 = trans2.transForm(P3);

                points->remove(1);
                points->insert(1,P2);
                points->remove(2);
                points->insert(2,P3);
                points->remove(0);
                points->insert(0,P1);
            }
            else
            {
                double* symmetry = getLineFromVector(TY,P3);
                double* P2Foot = normalFoot(symmetry,P2);
                P2 = QPointF(P2Foot[0]/P2Foot[2],P2Foot[1]/P2Foot[2]);
                P3 = P2;

                double* topLine = getLineFromVector(TX,P4);
                double* topMiddleP = VectorOuter(topLine,symmetry);
                QPointF topMid(topMiddleP[0]/topMiddleP[2],topMiddleP[1]/topMiddleP[2]);
                myTransform trans;
                trans.Translate(-topMid.x(),-topMid.y());
                trans.rotate(PI);
                trans.Translate(topMid.x(),topMid.y());
                P1 = trans.transForm(P4);

                points->remove(0);
                points->insert(0,P1);
                points->remove(1);
                points->insert(1,P2);
                points->remove(2);
                points->insert(2,P3);
                return;
            }

            return;
        }

        if( positionP1 == 0 && positionP2 == 0 )
        {

        }

        double* bottomLine = getLineFromVector(TX,P2);
        double* bottomRightP = VectorOuter(P3YLine,bottomLine);
        P3 = QPointF(bottomRightP[0]/bottomRightP[2],bottomRightP[1]/bottomRightP[2]);


        points->remove(0);
        points->insert(0,P1);
        points->remove(2);
        points->insert(2,P3);

        delete [] previousMiddleTopP;
        delete [] previousSymmetryLine;
        delete [] previousBottomLine;
        delete [] previousMiddleBottomP;
        delete [] foot;
        delete [] P3YLine;
        delete [] bottomLine;
        delete [] bottomRightP;
    }
    else//index = 3
    {
        double* previousMiddleTopP = middlePoint(P1,P4);
        double* previousSymmetryLine = getLineFromVector(TY,QPointF(previousMiddleTopP[0]/previousMiddleTopP[2],previousMiddleTopP[1]/previousMiddleTopP[2]));
        double* previousBottomLine = getLineFromVector(TX,P2);
        double* previousMiddleBottomP = VectorOuter(previousSymmetryLine,previousBottomLine);
        QPointF PMiddBottomP(previousMiddleBottomP[0]/previousMiddleBottomP[2],previousMiddleBottomP[1]/previousMiddleBottomP[2]);

        //上一次的P3点，对称出上一次的p2点。新P2点向上一次底边做垂线，垂足与上一次P2点之差就是P1移动的方向向量
        myTransform trans;
        trans.Translate(-PMiddBottomP.x(),-PMiddBottomP.y());
        trans.rotate(PI);
        trans.Translate(PMiddBottomP.x(),PMiddBottomP.y());
        QPointF previousP3 = trans.transForm(P2);

        double* foot = normalFoot(previousBottomLine,P3);
        QPointF footP3(foot[0]/foot[2],foot[1]/foot[2]);
        myTransform trans2;
        trans2.Translate(footP3.x()-previousP3.x(),footP3.y()-previousP3.y());
        P4 = trans2.transForm(P4);

        double* P1YLine = getLineFromVector(TY,P1);
        int positionP4 = positionPointAndLine(P4,P1YLine);
        double* P2YLine = getLineFromVector(TY,P2);
        int positionP3 = positionPointAndLine(P3,P2YLine);

        if( positionP3 <= 0 && positionP4 > 0 )
        {
            double* symmetry = getLineFromVector(TY,P2);
            double* P3Foot = normalFoot(symmetry,P3);
            P3 = QPointF(P3Foot[0]/P3Foot[2],P3Foot[1]/P3Foot[2]);
            P2 = P3;

            double* topLine = getLineFromVector(TX,P1);
            double* topMiddleP = VectorOuter(topLine,symmetry);
            QPointF topMid(topMiddleP[0]/topMiddleP[2],topMiddleP[1]/topMiddleP[2]);
            myTransform trans;
            trans.Translate(-topMid.x(),-topMid.y());
            trans.rotate(PI);
            trans.Translate(topMid.x(),topMid.y());
            P4 = trans.transForm(P1);

            points->remove(3);
            points->insert(3,P4);
            points->remove(1);
            points->insert(1,P2);
            points->remove(2);
            points->insert(2,P3);
            return;
        }


        if( positionP4 <= 0 && positionP3 > 0 )
        {
            //P3相对称轴作垂线，垂足PP3。上一次P3向对称轴作垂线，垂足与pp3之差就是p2移动的方向向量。
            //计算出最新的p2后对称出要求的p3
            P4 = P1;
            double* symmetry = getLineFromVector(TY,P1);
            double* P3Foot = normalFoot(symmetry,P3);
            double* P2Foot = normalFoot(symmetry,P2);
            QPointF P2FootP(P2Foot[0]/P2Foot[2],P2Foot[1]/P2Foot[2]);
            QPointF P3FootP(P3Foot[0]/P3Foot[2],P3Foot[1]/P3Foot[2]);

            myTransform trans;
            trans.Translate(P3FootP.x()-P2FootP.x(),P3FootP.y()-P2FootP.y());
            P2 = trans.transForm(P2);

            double* bottomLine = getLineFromVector(TX,P3);
            double* bottomMiddP = VectorOuter(bottomLine,symmetry);
            QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
            myTransform trans2;
            trans2.Translate(-bottomMid.x(),-bottomMid.y());
            trans2.rotate(PI);
            trans2.Translate(bottomMid.x(),bottomMid.y());
            P3 = trans2.transForm(P2);

            points->remove(1);
            points->insert(1,P2);
            points->remove(2);
            points->insert(2,P3);
            points->remove(3);
            points->insert(3,P4);
            return;
        }

        if( positionP4 < 0 && positionP3 < 0 )
        {
            int p2Postion = positionPointAndLine(P2,P1YLine);
            if( p2Postion <= 0 )
            {
                //P2相对称轴作垂线，垂足PP2。上一次P3向对称轴作垂线，垂足与pp2只差就是p3移动的方向向量。
                //计算出最新的p3后对称出要求的p2
                P4 = P1;
                double* symmetry = getLineFromVector(TY,P1);
                double* P2Foot = normalFoot(symmetry,P2);
                double* P3Foot = normalFoot(symmetry,P3);
                QPointF P2FootP(P2Foot[0]/P2Foot[2],P2Foot[1]/P2Foot[2]);
                QPointF P3FootP(P3Foot[0]/P3Foot[2],P3Foot[1]/P3Foot[2]);

                myTransform trans;
                trans.Translate(P3FootP.x()-P2FootP.x(),P3FootP.y()-P2FootP.y());
                P2 = trans.transForm(P2);

                double* bottomLine = getLineFromVector(TX,P3);
                double* bottomMiddP = VectorOuter(bottomLine,symmetry);
                QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
                myTransform trans2;
                trans2.Translate(-bottomMid.x(),-bottomMid.y());
                trans2.rotate(PI);
                trans2.Translate(bottomMid.x(),bottomMid.y());
                P3 = trans2.transForm(P2);

                points->remove(1);
                points->insert(1,P2);
                points->remove(2);
                points->insert(2,P3);
                points->remove(3);
                points->insert(3,P4);
            }
            else
            {
                double* symmetry = getLineFromVector(TY,P2);
                double* P3Foot = normalFoot(symmetry,P3);
                P3 = QPointF(P3Foot[0]/P3Foot[2],P3Foot[1]/P3Foot[2]);
                P2 = P3;

                double* topLine = getLineFromVector(TX,P1);
                double* topMiddleP = VectorOuter(topLine,symmetry);
                QPointF topMid(topMiddleP[0]/topMiddleP[2],topMiddleP[1]/topMiddleP[2]);
                myTransform trans;
                trans.Translate(-topMid.x(),-topMid.y());
                trans.rotate(PI);
                trans.Translate(topMid.x(),topMid.y());
                P4 = trans.transForm(P1);

                points->remove(3);
                points->insert(3,P4);
                points->remove(1);
                points->insert(1,P2);
                points->remove(2);
                points->insert(2,P3);
                return;
            }

            return;
        }

        if( positionP4 == 0 && positionP3 == 0 )
        {

        }

        double* bottomLine = getLineFromVector(TX,P3);
        double* bottomRightP = VectorOuter(P2YLine,bottomLine);
        P2 = QPointF(bottomRightP[0]/bottomRightP[2],bottomRightP[1]/bottomRightP[2]);


        points->remove(3);
        points->insert(3,P4);
        points->remove(1);
        points->insert(1,P2);

        delete [] previousMiddleTopP;
        delete [] previousSymmetryLine;
        delete [] previousBottomLine;
        delete [] previousMiddleBottomP;
        delete [] foot;
        delete [] P2YLine;
        delete [] bottomLine;
        delete [] bottomRightP;
    }

    delete [] TX;
    delete [] TY;

    refresh(points);
}
