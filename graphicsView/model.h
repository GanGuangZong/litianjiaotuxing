#ifndef MODEL_H
#define MODEL_H

#include <QPointF>
#include <QVector>



class Model
{
public:

    enum shapeType{
        Rhombus,
        Rect,
        Square,
        Parallelogram,
        Echelon,
        EqualEchelon,
        OrthometricEchelon,
    };

    Model();
    QList<QPointF> *createRhombus(double rotate);
    QList<QPointF> *createRect(double rotate);
    QList<QPointF> *createSquare(double rotate);
    QList<QPointF> *createParallelogram(double rotate);
    QList<QPointF> *createEchelon(double rotate);
    QList<QPointF> *createEqualEchelon(double rotate);
    QList<QPointF> *createOrthometricEchelon(double rotate);
};

#endif // MODEL_H
