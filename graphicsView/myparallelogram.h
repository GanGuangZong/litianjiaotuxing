#ifndef MYPARALLELOGRAM_H
#define MYPARALLELOGRAM_H

#include "myitem.h"

class myParallelogram : public myItem
{
public:
    myParallelogram();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYPARALLELOGRAM_H
