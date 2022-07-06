#include "widget.h"
#include "SKTransform.h"
#include <QMouseEvent>
#include <QDebug>
const double PI = 4.0 * atan(1.0);
Widget::Widget(QWidget *parent)
    : QGraphicsView(parent)
{
    m_rotate = ( 0 * PI) / 180.0;
    //setFixedSize(200,200);
    setSceneRect(QRectF(0, 0, 200, 200));
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(QRectF(0, 0, 200, 200));
    m_scene->addLine(0,-100,0,100);
    m_scene->addLine(-100,0,100,0);
    this->setScene(m_scene);
    m_item = new QGraphicsPolygonItem();
    m_points = createShape(m_rotate);
    QPolygonF poly(*m_points);
    m_item->setPolygon(poly);
    m_item->setPos(0,0);
    m_scene->addItem(m_item);
    m_scene->update(m_item->boundingRect());
}

Widget::~Widget()
{

}

void Widget::mousePressEvent(QMouseEvent *e)
{
    QPointF p = e->pos();
    p = mapToScene(p.toPoint());
    QRectF posR(p.x() - 3,p.y() -3, 6, 6);
    for(int i=0; i<m_points->count(); i++)
    {
        if(posR.contains(m_points->at(i)))
            m_index = i;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_index == -1)
    {

        return;
    }
    QPointF actionP = mapToScene( e->pos());
    m_points->removeAt(m_index);
    m_points->insert(m_index,actionP);

    reSetShape(m_points,m_index,m_rotate);

    QPolygonF poly(*m_points);
    m_item->setPolygon(poly);
    m_item->update();
    m_scene->update(m_item->boundingRect());
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    m_index = -1;
}

QVector<QPointF> *Widget::createShape(double rotate)
{
    QVector<QPointF> *points = nullptr;
    if(m_t == 0)
        points = createRect(rotate);
    else if(m_t == 1)
        points = createRhombus(rotate);
    else if(m_t == 2)
        points = createSquare(rotate);
    else if(m_t == 3)
        points = createParallelogram(rotate);
    else if(m_t == 4)
        points = createEchelon(rotate);
    else if(m_t == 5)
        points = createEqualEchelon(rotate);
    else if(m_t == 6)
        points = createOrthometricEchelon(rotate);
    return points;
}

void Widget::reSetShape(QVector<QPointF> *points, int index,double rotate)
{
    if( m_t == 0 )
        computeRectangle(points,index,rotate);
    else if( m_t == 1)
        computeRhombus(points,index,rotate);
    else if(m_t == 2)
        computeSquare(points,index,rotate);
    else if(m_t == 3)
        computeParallelogram(points,index,rotate);
    else if(m_t == 4)
        computeEchelon(points,index,rotate);
    else if(m_t == 5)
        computeEqualEchelon(points,index,rotate);
    else if(m_t == 6)
        computeOrthometricEchelon(points,index,rotate);
}

QPointF Widget::getCenterPoint(QVector<QPointF> *points)
{
    double top=points->at(0).y(), bottom=points->at(0).y(), left=points->at(0).x(), right=points->at(0).x();
    QVector<QPointF>::iterator it;
    for (it = points->begin(); it != points->end(); it++)
    {
        if((*it).y() < top)
            top = (*it).y();
        if ((*it).y() > bottom)
            bottom = (*it).y();
        if ((*it).x() < left)
            left = (*it).x();
        if ((*it).x() > right)
            right = (*it).x();
    }
    return QPointF(left+(right-left)/2,top+(bottom-top)/2);
}

double *Widget::getLine(QPointF p1, QPointF p2)//点的外积是直线
{
    double tp1[3] = {p1.x(),p1.y(),1};
    double tp2[3] = {p2.x(),p2.y(),1};
    return VectorOuter(tp1,tp2);
}

double *Widget::getLineFromVector(double v1[], QPointF p1)//直线的点向式
{
    return new double[3]{v1[1],-v1[0],v1[0]*p1.y()-v1[1]*p1.x()};
}

double *Widget::VectorOuter(double v1[], double v2[])//向量外积
{
    double* out = new double[3];
    out[0] = v1[1]*v2[2] - v2[1]*v1[2];
    out[1] = v2[0]*v1[2] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v2[0]*v1[1];
    return out;
}

int Widget::vectorInner(double v1[], double v2[])
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

double *Widget::middlePoint(QPointF p1, QPointF p2)//中点向量
{
    double* out = new double[3];
    double pv1[3] = {p1.x(),p1.y(),1};
    double pv2[3] = {p2.x(),p2.y(),1};
    for(int i=0;i<3;i++)
    {
        out[i] = (pv1[i] + pv2[i])/2;
    }
    return out;
}

double *Widget::normalFoot(double l[], QPointF p)
{
    double normal[3] = {l[0],l[1],0};//法向量
    double* normalLine = getLineFromVector(normal,p);
    double* normalPoint = VectorOuter(l,normalLine);
    delete[] normalLine;
    return normalPoint;
}

double *Widget::getVector(QPointF p1, QPointF p2)
{
    return new double[3]{p2.x()-p1.x(),p2.y()-p1.y(),0};
}

void Widget::computeRectangle(QVector<QPointF> *points, int index, double rotate)
{
    QPointF actionP = points->at(index);
    QPointF lastP = points->at((index+3)%4);
    QPointF opposetP = points->at((index+2)%4);
    QPointF nextP  = points->at((index+1)%4);

    double lineVectorY[3] = {0,1,0};//x轴方向向量
    double lineVectorX[3] = {1,0,0};//x轴方向向量

    SKTransform trans;
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
}

void Widget::computeRhombus(QVector<QPointF> *points, int index, double rotate)
{
    Q_UNUSED(rotate)
    QPointF actionP = points->at(index);
    QPointF lastP = points->at((index+3)%4);
    QPointF opposetP = points->at((index+2)%4);
    QPointF nextP  = points->at((index+1)%4);

    double* diagonal1 = getLine(lastP,nextP);
    SKTransform trans;
    trans.rotate(PI/2);
    double* diagonal2 = trans.transForm(diagonal1);
    double* normalPoint = normalFoot(diagonal2,actionP);
    actionP = QPoint(normalPoint[0]/normalPoint[2],normalPoint[1]/normalPoint[2]);
    SKTransform trans2;
    trans2.rotate(PI);
    opposetP = trans2.transForm(actionP);

    points->remove(index);
    points->insert(index,actionP);
    points->remove((index+2)%4);
    points->insert((index+2)%4,opposetP);

    delete[] diagonal1;
    delete[] diagonal2;
    delete[] normalPoint;
}

void Widget::computeSquare(QVector<QPointF> *points, int index, double rotate)
{
    QPointF actionP = points->at(index);
    QPointF lastP = points->at((index+3)%4);
    QPointF opposetP = points->at((index+2)%4);
    QPointF nextP  = points->at((index+1)%4);

    double lineVectorY[3] = {0,1,0};//x轴方向向量
    double lineVectorX[3] = {1,0,0};//x轴方向向量
    SKTransform trans;
    trans.rotate(rotate);//旋转向量以适应矩形角度
    double *TX = trans.transForm(lineVectorX);//旋转后X轴向量
    double *TY = trans.transForm(lineVectorY);//旋转后Y轴向量

    SKTransform trans1;
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

    SKTransform trans3;
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
}

void Widget::computeParallelogram(QVector<QPointF> *points, int index, double rotate)
{
    Q_UNUSED(rotate)
    QPointF actionP = points->at(index);
    //QPointF opposetP = points->at((index+2)%4);
    QPointF lastP = points->at((index+3)%4);
    QPointF nextP  = points->at((index+1)%4);

    double* middleP = middlePoint(nextP,lastP);
    QPointF middle(middleP[0]/middleP[2],middleP[1]/middleP[2]);
    SKTransform trans;
    trans.Translate(-middle.x(),-middle.y());
    trans.rotate(PI);
    trans.Translate(middle.x(),middle.y());
    QPointF opposetP = trans.transForm(actionP);

    points->remove((index+2)%4);
    points->insert((index+2)%4,opposetP);

    delete [] middleP;
}

void Widget::computeEchelon(QVector<QPointF> *points, int index, double rotate)//梯形规定14为上底23为下底12和34分别为斜边
{
    QPointF actionP = points->at(index);
    QPointF opposetP = points->at((index+2)%4);
    QPointF lastP = points->at((index+3)%4);
    QPointF nextP  = points->at((index+1)%4);
    double lineVectorX[3] = {1,0,0};
    double lineVectorY[3] = {0,1,0};
    SKTransform trans;
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
}

void Widget::computeEqualEchelon(QVector<QPointF> *points, int index, double rotate)
{
    QPointF P1 = points->at(0);
    QPointF P3 = points->at(2);
    QPointF P4 = points->at(3);
    QPointF P2  = points->at(1);
    double lineVectorX[3] = {1,0,0};
    double lineVectorY[3] = {0,1,0};
    SKTransform trans;
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
        SKTransform trans;
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
        SKTransform trans;
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
        SKTransform trans;
        trans.Translate(-PMiddBottomP.x(),-PMiddBottomP.y());
        trans.rotate(PI);
        trans.Translate(PMiddBottomP.x(),PMiddBottomP.y());
        QPointF previousP2 = trans.transForm(P3);

        double* foot = normalFoot(previousBottomLine,P2);
        QPointF footP2(foot[0]/foot[2],foot[1]/foot[2]);
        SKTransform trans2;
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
            SKTransform trans;
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

            SKTransform trans;
            trans.Translate(P2FootP.x()-P3FootP.x(),P2FootP.y()-P3FootP.y());
            P3 = trans.transForm(P3);

            double* bottomLine = getLineFromVector(TX,P2);
            double* bottomMiddP = VectorOuter(bottomLine,symmetry);
            QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
            SKTransform trans2;
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

                SKTransform trans;
                trans.Translate(P2FootP.x()-P3FootP.x(),P2FootP.y()-P3FootP.y());
                P3 = trans.transForm(P3);

                double* bottomLine = getLineFromVector(TX,P2);
                double* bottomMiddP = VectorOuter(bottomLine,symmetry);
                QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
                SKTransform trans2;
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
                SKTransform trans;
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
        SKTransform trans;
        trans.Translate(-PMiddBottomP.x(),-PMiddBottomP.y());
        trans.rotate(PI);
        trans.Translate(PMiddBottomP.x(),PMiddBottomP.y());
        QPointF previousP3 = trans.transForm(P2);

        double* foot = normalFoot(previousBottomLine,P3);
        QPointF footP3(foot[0]/foot[2],foot[1]/foot[2]);
        SKTransform trans2;
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
            SKTransform trans;
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

            SKTransform trans;
            trans.Translate(P3FootP.x()-P2FootP.x(),P3FootP.y()-P2FootP.y());
            P2 = trans.transForm(P2);

            double* bottomLine = getLineFromVector(TX,P3);
            double* bottomMiddP = VectorOuter(bottomLine,symmetry);
            QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
            SKTransform trans2;
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

                SKTransform trans;
                trans.Translate(P3FootP.x()-P2FootP.x(),P3FootP.y()-P2FootP.y());
                P2 = trans.transForm(P2);

                double* bottomLine = getLineFromVector(TX,P3);
                double* bottomMiddP = VectorOuter(bottomLine,symmetry);
                QPointF bottomMid(bottomMiddP[0]/bottomMiddP[2],bottomMiddP[1]/bottomMiddP[2]);
                SKTransform trans2;
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
                SKTransform trans;
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
}

void Widget::computeOrthometricEchelon(QVector<QPointF> *points, int index, double rotate)
{
    QPointF P1 = points->at(0);
    QPointF P3 = points->at(2);
    QPointF P4 = points->at(3);
    QPointF P2  = points->at(1);

    double lineVectorX[3] = {1,0,0};
    double lineVectorY[3] = {0,1,0};
    SKTransform trans;
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
}

int Widget::positionPointAndLine(QPointF p, double l[])
{
    return l[0]*p.x() + l[1]*p.y() + l[2];
}

QVector<QPointF> *Widget::createRhombus(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(0,8);
    points->push_back(p);
    p =  QPointF(-10,0);
    points->push_back(p);
    p =  QPointF(0,-8);
    points->push_back(p);
    p =  QPointF(10,0);
    //p =  QPointF(0,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    return points;
}

QVector<QPointF> *Widget::createRect(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(0,0);
    points->push_back(p);
    p =  QPointF(0,8);
    points->push_back(p);
    p =  QPointF(10,8);
    points->push_back(p);
    p =  QPointF(10,0);
    //p =  QPointF(0,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    return points;
}

QVector<QPointF> *Widget::createSquare(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(0,0);
    points->push_back(p);
    p =  QPointF(0,80);
    points->push_back(p);
    p =  QPointF(80,80);
    points->push_back(p);
    p =  QPointF(80,0);
    //p =  QPointF(0,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    return points;
}

QVector<QPointF> *Widget::createParallelogram(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(0,8);
    points->push_back(p);
    p =  QPointF(10,8);
    points->push_back(p);
    p =  QPointF(13,0);
    points->push_back(p);
    p =  QPointF(5,0);
    //p =  QPointF(0,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    return points;
}

QVector<QPointF> *Widget::createEchelon(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(50,0);
    points->push_back(p);
    p =  QPointF(0,70);
    points->push_back(p);
    p =  QPointF(130,70);
    points->push_back(p);
    p =  QPointF(110,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);
    return points;
}

QVector<QPointF> *Widget::createEqualEchelon(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(30,0);
    points->push_back(p);
    p =  QPointF(0,70);
    points->push_back(p);
    p =  QPointF(120,70);
    points->push_back(p);
    p =  QPointF(90,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);
    return points;
}

QVector<QPointF> *Widget::createOrthometricEchelon(double rotate)
{
    QVector<QPointF> *points = new QVector<QPointF>();
    QPointF p(0,0);
    points->push_back(p);
    p =  QPointF(0,70);
    points->push_back(p);
    p =  QPointF(130,70);
    points->push_back(p);
    p =  QPointF(50,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    m_scene->addEllipse(middle[0], middle[1], 1, 1);
    SKTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);
    return points;
}
