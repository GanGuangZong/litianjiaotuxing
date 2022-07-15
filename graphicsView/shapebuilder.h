#ifndef SHAPEBUILDER_H
#define SHAPEBUILDER_H

#include "myitem.h"
#include "model.h"
#include <QVector>
#include <QPointF>

class shapeBuilder
{
public:
    shapeBuilder();
    myItem* createShape(Model::shapeType type, double rotate);
};

#endif // SHAPEBUILDER_H
