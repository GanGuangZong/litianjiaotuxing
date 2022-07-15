#ifndef MYECHELON_H
#define MYECHELON_H

#include "myitem.h"

class myEchelon : public myItem
{
public:
    myEchelon();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYECHELON_H
