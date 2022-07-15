#ifndef MYEQUALECHELON_H
#define MYEQUALECHELON_H

#include "myitem.h"

class myEqualEchelon : public myItem
{
public:
    myEqualEchelon();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYEQUALECHELON_H
