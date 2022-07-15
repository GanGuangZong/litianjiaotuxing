#ifndef MYSQUARE_H
#define MYSQUARE_H

#include "myitem.h"

class mySquare : public myItem
{
public:
    mySquare();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYSQUARE_H
