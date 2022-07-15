#include "geometry.h"

QPointF getCenterPoint(QVector<QPointF> *points)
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

double *getLine(QPointF p1, QPointF p2)//点的外积是直线
{
    double tp1[3] = {p1.x(),p1.y(),1};
    double tp2[3] = {p2.x(),p2.y(),1};
    return VectorOuter(tp1,tp2);
}

double *getLineFromVector(double v1[], QPointF p1)//直线的点向式
{
    return new double[3]{v1[1],-v1[0],v1[0]*p1.y()-v1[1]*p1.x()};
}

double *VectorOuter(double v1[], double v2[])//向量外积
{
    double* out = new double[3];
    out[0] = v1[1]*v2[2] - v2[1]*v1[2];
    out[1] = v2[0]*v1[2] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v2[0]*v1[1];
    return out;
}

int vectorInner(double v1[], double v2[])
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

double *middlePoint(QPointF p1, QPointF p2)//中点向量
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

double *normalFoot(double l[], QPointF p)
{
    double normal[3] = {l[0],l[1],0};//法向量
    double* normalLine = getLineFromVector(normal,p);
    double* normalPoint = VectorOuter(l,normalLine);
    delete[] normalLine;
    return normalPoint;
}

double *getVector(QPointF p1, QPointF p2)
{
    return new double[3]{p2.x()-p1.x(),p2.y()-p1.y(),0};
}

int positionPointAndLine(QPointF p, double l[])
{
    return l[0]*p.x() + l[1]*p.y() + l[2];
}
