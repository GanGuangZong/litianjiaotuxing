#include "model.h"
#include "myTransform.h"
#include "geometry.h"



Model::Model()
{

}

QList<QPointF> *Model::createRhombus(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
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
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    return points;
}

QList<QPointF> *Model::createRect(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
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
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    return points;
}

QList<QPointF> *Model::createSquare(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
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
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    return points;
}

QList<QPointF> *Model::createParallelogram(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
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
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);

    middle = middlePoint(points->at(0),points->at(2));
    return points;
}

QList<QPointF> *Model::createEchelon(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
    QPointF p(50,0);
    points->push_back(p);
    p =  QPointF(0,70);
    points->push_back(p);
    p =  QPointF(130,70);
    points->push_back(p);
    p =  QPointF(110,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);
    return points;
}

QList<QPointF> *Model::createEqualEchelon(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
    QPointF p(30,0);
    points->push_back(p);
    p =  QPointF(0,70);
    points->push_back(p);
    p =  QPointF(120,70);
    points->push_back(p);
    p =  QPointF(90,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);
    return points;
}

QList<QPointF> *Model::createOrthometricEchelon(double rotate)
{
    QList<QPointF> *points = new QList<QPointF>();
    QPointF p(0,0);
    points->push_back(p);
    p =  QPointF(0,70);
    points->push_back(p);
    p =  QPointF(130,70);
    points->push_back(p);
    p =  QPointF(50,0);
    points->push_back(p);
    double* middle = middlePoint(points->at(0),points->at(2));
    myTransform trans;
    trans.Translate(-middle[0],-middle[1]);
    trans.rotate(rotate);
    trans.Translate(middle[0],middle[1]);
    trans.transForm(points);
    return points;
}
