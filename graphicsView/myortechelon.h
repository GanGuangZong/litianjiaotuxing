#ifndef MYORTECHELON_H
#define MYORTECHELON_H

#include "myitem.h"

class myOrtEchelon : public myItem
{
public:
    myOrtEchelon();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYORTECHELON_H
