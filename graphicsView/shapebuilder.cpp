#include "shapebuilder.h"
#include "myrect.h"
#include "myechelon.h"
#include "myequalechelon.h"
#include "myortechelon.h"
#include "myparallelogram.h"
#include "myrhombus.h"
#include "mysquare.h"

shapeBuilder::shapeBuilder()
{

}


myItem* shapeBuilder::createShape(Model::shapeType type, double rotate)
{
    Model M;
    myItem* item = nullptr;
    QList<QPointF>* points = nullptr;
    switch(type)
    {
    case Model::shapeType::Rect:
        points = M.createRect(rotate);
        item = new myRect();
        item->refresh(points);
        break;
    case Model::shapeType::Rhombus:
        points = M.createRhombus(rotate);
        item = new myRhombus();
        item->refresh(points);
        break;
    case Model::shapeType::Square:
        points = M.createSquare(rotate);
        item = new mySquare();
        item->refresh(points);
        break;
    case Model::shapeType::Parallelogram:
        points = M.createParallelogram(rotate);
        item = new myParallelogram();
        item->refresh(points);
        break;
    case Model::shapeType::Echelon:
        points = M.createEchelon(rotate);
        item = new myEchelon();
        item->refresh(points);
        break;
    case Model::shapeType::EqualEchelon:
        points = M.createEqualEchelon(rotate);
        item = new myEqualEchelon();
        item->refresh(points);
        break;
    case Model::shapeType::OrthometricEchelon:
        points = M.createOrthometricEchelon(rotate);
        item = new myOrtEchelon();
        item->refresh(points);
        break;
    }
    points->clear();
    delete points;
    return item;
}
