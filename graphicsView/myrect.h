#ifndef MYRECT_H
#define MYRECT_H

#include "myitem.h"

class myRect : public myItem
{
public:
    myRect();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYRECT_H
