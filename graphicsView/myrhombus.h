#ifndef MYRHOMBUS_H
#define MYRHOMBUS_H

#include "myitem.h"

class myRhombus : public myItem
{
public:
    myRhombus();
    virtual void reSetShape(QList<QPointF> * points, int index, double rotate);
};

#endif // MYRHOMBUS_H
