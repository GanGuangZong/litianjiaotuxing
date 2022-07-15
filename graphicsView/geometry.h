#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QPointF>
#include <QVector>

QPointF getCenterPoint(QVector<QPointF> * points);
double* getLine(QPointF p1,QPointF p2);
double* getLineFromVector(double v1[], QPointF p1);
double* VectorOuter(double v1[], double v2[]);
int vectorInner(double v1[], double v2[]);
double* middlePoint(QPointF p1,QPointF p2);
double* normalFoot(double l[],QPointF p);
double* getVector(QPointF p1, QPointF p2);
int positionPointAndLine(QPointF p, double l[]);

#endif // GEOMETRY_H
